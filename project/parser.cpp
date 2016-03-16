#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct gtexAnalysisFile_t {
	string header;
	unsigned int genesNum, samplesNum;

	vector<string> genesHeader;
	vector<vector<string>> genesData;
};

void tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ") {
	// skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// add empty string tokens between contiguous delimiters
	for (unsigned int i = 0; i < lastPos && string::npos != lastPos; i++)
		tokens.push_back("");

	// find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		// found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// skip delimiters. Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// add empty string tokens between contiguous delimiters
		for (unsigned int i = 0; i < lastPos - pos - 1 && string::npos != lastPos; i++)
			tokens.push_back("");

		// find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

vector<string> splitTSV(const string& str) {
	vector<string> tokens;

	tokenize(str, tokens, "\t");

	return tokens;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: Too few arguments" << endl;
		return 1;
	}

	string line;

	/*
	* Read genes file header (the ~5gb .txt file)
	*/
	ifstream gtexAnalysisIn;
	gtexAnalysisIn.open(argv[1]);

	gtexAnalysisFile_t gtexAnalysisFile;
	gtexAnalysisIn >> gtexAnalysisFile.header;

	gtexAnalysisIn >> gtexAnalysisFile.genesNum >> gtexAnalysisFile.samplesNum;
	gtexAnalysisIn.ignore();

	cout << "-----------------" << endl;
	cout << "No. genes: " << gtexAnalysisFile.genesNum << endl;
	cout << "No. samples: " << gtexAnalysisFile.samplesNum << endl;
	cout << "-----------------" << endl;

	getline(gtexAnalysisIn, line);

	gtexAnalysisFile.genesHeader = splitTSV(line);

	// this map makes it possible to return the column of a certain sample in O(1)
	map<string, unsigned int> sampleColumnMap;

	/*
	* Build [tissue -> samples] multimap
	*/
	ifstream gtexDataIn;
	gtexDataIn.open(argv[2]);
	getline(gtexDataIn, line);

	multimap<string,string> tissueSampleMap;

	for (unsigned int i = 0; i < gtexAnalysisFile.samplesNum; i++) {
		getline(gtexDataIn, line);

		vector<string> tokens = splitTSV(line);

		tissueSampleMap.insert(pair<string, string>(tokens[6], tokens[0]));
	}

	// ignore tissues with less than 10 samples
	for(auto it = tissueSampleMap.begin(), end = tissueSampleMap.end(); it != end; it = tissueSampleMap.upper_bound(it->first)) {
		if (tissueSampleMap.count(it->first) < 10)
			tissueSampleMap.erase(it->first);
	}

	for (auto it = tissueSampleMap.begin(), end = tissueSampleMap.end(); it != end; it = tissueSampleMap.upper_bound(it->first))
		cout << it->first << " -> " << tissueSampleMap.count(it->first) << endl;


	/*
	* Output genes file for each tissue
	*/
	for (auto it = tissueSampleMap.begin(), end = tissueSampleMap.end(); it != end; it = tissueSampleMap.upper_bound(it->first)) {
		ofstream gtexAnalysisCopyOut;
		gtexAnalysisCopyOut.open("gtex/rna-seq-data/tissues-output/" + it->first + ".txt");

		gtexAnalysisCopyOut << gtexAnalysisFile.header << endl;
		gtexAnalysisCopyOut << gtexAnalysisFile.genesNum << "\t" << gtexAnalysisFile.samplesNum << endl;

		for (unsigned int i = 0; i < gtexAnalysisFile.genesHeader.size(); i++) {
			gtexAnalysisCopyOut << gtexAnalysisFile.genesHeader[i];

			gtexAnalysisCopyOut << (i == gtexAnalysisFile.genesHeader.size() - 1 ? "\n" : "\t");
		}

		gtexAnalysisCopyOut.close();
	}

	return 0;
}

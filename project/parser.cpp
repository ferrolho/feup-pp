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

	cout << "> Reading giant genes file (~5gb takes time, go grab a snack) ... " << flush;

	getline(gtexAnalysisIn, line);
	gtexAnalysisFile.genesHeader = splitTSV(line);

	for (unsigned int i = 0; i < gtexAnalysisFile.genesNum; i++) {
		getline(gtexAnalysisIn, line);
		gtexAnalysisFile.genesData.push_back(splitTSV(line));
	}

	gtexAnalysisIn.close();
	cout << "OK!" << endl;	

	// this map makes it possible to return the column of a certain sample in O(1)
	map<string, unsigned int> sampleColumnMap;

	for (unsigned int i = 0; i < gtexAnalysisFile.genesHeader.size(); i++)
		sampleColumnMap[gtexAnalysisFile.genesHeader[i]] = i;

	/*
	* Build [tissue -> samples] multimap
	*/
	cout << "> Reading samples file ... " << flush;

	ifstream gtexDataIn;
	gtexDataIn.open(argv[2]);
	getline(gtexDataIn, line);

	multimap<string,string> tissueSamplesMap;

	for (unsigned int i = 0; i < gtexAnalysisFile.samplesNum; i++) {
		getline(gtexDataIn, line);

		vector<string> tokens = splitTSV(line);

		tissueSamplesMap.insert(pair<string, string>(tokens[6], tokens[0]));
	}

	gtexDataIn.close();
	cout << "OK!" << endl;

	// ignore tissues with less than 10 samples
	for (auto it = tissueSamplesMap.cbegin(); it != tissueSamplesMap.cend();) {
		if (tissueSamplesMap.count(it->first) < 10) {
			auto nextIt = tissueSamplesMap.upper_bound(it->first);

			tissueSamplesMap.erase(it->first);

			it = nextIt;
		} else {
			it = tissueSamplesMap.upper_bound(it->first);
		}
	}

	//for (auto it = tissueSamplesMap.begin(), end = tissueSamplesMap.end(); it != end; it = tissueSamplesMap.upper_bound(it->first))
	//	cout << it->first << " -> " << tissueSamplesMap.count(it->first) << endl;

	/*
	* Output genes file for each tissue
	*/
	for (auto it = tissueSamplesMap.begin(), end = tissueSamplesMap.end(); it != end; it = tissueSamplesMap.upper_bound(it->first)) {
		string tissueName = it->first;

		cout << "> Generating " << tissueName << ".txt ... " << flush;

		ofstream fout;
		fout.open("gtex/rna-seq-data/tissues-output/" + tissueName + ".txt");

		fout << gtexAnalysisFile.header << endl;
		fout << gtexAnalysisFile.genesNum << "\t" << tissueSamplesMap.count(tissueName) << endl;

		// Name and Description columns headers
		for (unsigned int i = 0; i < 2; i++)
			fout << gtexAnalysisFile.genesHeader[i] << "\t";

		auto samplesRange = tissueSamplesMap.equal_range(tissueName);
		for (auto it = samplesRange.first; it != samplesRange.second;) {
			fout << it->second;

			fout << (++it != samplesRange.second ? "\t" : "\n");
		}

		for (auto geneData : gtexAnalysisFile.genesData) {
			// Name and Description columns data
			for (unsigned int i = 0; i < 2; i++)
				fout << geneData[i] << "\t";

			for (auto it = samplesRange.first; it != samplesRange.second;) {
				// some samples are not present in the giant genes file; they are marked as N/A in the output files
				fout << (sampleColumnMap[it->second] < 2 ? "N/A" : geneData[sampleColumnMap[it->second]]);

				fout << (++it != samplesRange.second ? "\t" : "\n");
			}
		}

		fout.close();

		cout << "OK!" << endl;
	}

	return 0;
}

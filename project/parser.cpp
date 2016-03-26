#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <vector>
#include <sstream>
using namespace std;

struct giantGenesFile_t {
	string header;
	unsigned int genesNum, samplesNum;

	vector<string> genesHeader;
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

multimap<string, string> buildTissueToSamplesMap(const string& samplesFilename, const giantGenesFile_t& giantGenesFile, map<string, unsigned int>& sampleColumnMap) {
	ifstream gtexDataIn;
	gtexDataIn.open(samplesFilename);

	cout << endl << "> Reading samples file ... " << flush;

	string line;
	getline(gtexDataIn, line);

	multimap<string, string> tissueSamplesMap;

	while (getline(gtexDataIn, line)) {
		vector<string> tokens = splitTSV(line);

		if (sampleColumnMap[tokens[0]] >= 2)
			tissueSamplesMap.emplace(tokens[6], tokens[0]);
	}

	gtexDataIn.close();

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

	cout << "OK!" << endl << endl;

	return tissueSamplesMap;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: Too few arguments" << endl;
		return 1;
	}

	/*
	* Read genes file header (the ~5gb .txt file)
	*/
	ifstream gtexAnalysisIn;
	gtexAnalysisIn.open(argv[1]);

	giantGenesFile_t giantGenesFile;
	gtexAnalysisIn >> giantGenesFile.header;

	gtexAnalysisIn >> giantGenesFile.genesNum >> giantGenesFile.samplesNum;
	gtexAnalysisIn.ignore();

	cout << "-----------------" << endl;
	cout << "No. genes: " << giantGenesFile.genesNum << endl;
	cout << "No. samples: " << giantGenesFile.samplesNum << endl;
	cout << "-----------------" << endl;

	string line;

	getline(gtexAnalysisIn, line);
	giantGenesFile.genesHeader = splitTSV(line);

	// this map makes it possible to return the column of a certain sample in O(1)
	map<string, unsigned int> sampleColumnMap;
	for (unsigned int i = 0; i < giantGenesFile.genesHeader.size(); i++)
		sampleColumnMap[giantGenesFile.genesHeader[i]] = i;

	/*
	* Build [tissue -> samples] multimap
	*/
	multimap<string, string> tissueSamplesMap = buildTissueToSamplesMap(argv[2], giantGenesFile, sampleColumnMap);


	// maps each tissue name to its file output stream
	map<string, shared_ptr<ofstream>> tissuesFilesMap;

	ostringstream outputStream;

	/*
	* Output genes header for each tissue file
	*/
	for (auto it = tissueSamplesMap.begin(), end = tissueSamplesMap.end(); it != end; it = tissueSamplesMap.upper_bound(it->first)) {
		string tissueName = it->first;

		cout << "> Opening " << tissueName << ".txt ... " << flush;

		string filename = "gtex/rna-seq-data/tissues-output/" + tissueName + ".txt";
		tissuesFilesMap[tissueName] = make_shared<ofstream> (filename);

		// resetting stream
		outputStream.str(string());
		outputStream.clear();

		outputStream << giantGenesFile.header << endl;
		outputStream << giantGenesFile.genesNum << '\t' << tissueSamplesMap.count(tissueName) << endl;

		// Name and Description columns headers
		for (unsigned int i = 0; i < 2; i++)
			outputStream << giantGenesFile.genesHeader[i] << '\t';

		auto samplesRange = tissueSamplesMap.equal_range(tissueName);
		for (auto it = samplesRange.first; it != samplesRange.second; it++)
			outputStream << it->second << (next(it) != samplesRange.second ? '\t' : '\n');

		*tissuesFilesMap[tissueName] << outputStream.str();

		cout << "OK!" << endl;
	}

	cout << endl << "> Reading giant genes file (~5gb takes time, go grab a snack) ..." << endl;

	for (unsigned int i = 0; i < giantGenesFile.genesNum; i++) {
		getline(gtexAnalysisIn, line);
		vector<string> geneData = splitTSV(line);

		for (auto pair : tissuesFilesMap) {
			// resetting stream
			outputStream.str(string());
			outputStream.clear();

			// Name and Description columns data
			for (unsigned int i = 0; i < 2; i++)
				outputStream << geneData[i] << "\t";

			string tissueName = pair.first;

			auto samplesRange = tissueSamplesMap.equal_range(tissueName);
			for (auto it = samplesRange.first; it != samplesRange.second; it++)
				outputStream << geneData[sampleColumnMap[it->second]] << (next(it) != samplesRange.second ? '\t' : '\n');

			*tissuesFilesMap[tissueName] << outputStream.str();
		}

		printf("\r%5.1f %%", (i + 1) * 100.0 / giantGenesFile.genesNum);
	}

	gtexAnalysisIn.close();
	cout << " OK!" << endl << endl;

	for (auto pair : tissuesFilesMap) {
		cout << "> Closing " << pair.first << ".txt ... " << flush;

		pair.second->close();

		cout << "OK!" << endl;
	}

	cout << endl;

	return 0;
}

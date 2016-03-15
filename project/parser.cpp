#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

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

	ifstream gtexAnalysis;
	gtexAnalysis.open(argv[1]);
	getline(gtexAnalysis, line);

	unsigned int genesNum, samplesNum;
	gtexAnalysis >> genesNum >> samplesNum;
	gtexAnalysis.ignore();

	cout << "-----------------" << endl;
	cout << "No. genes: " << genesNum << endl;
	cout << "No. samples: " << samplesNum << endl;
	cout << "-----------------" << endl;


	ifstream gtexData;
	gtexData.open(argv[2]);
	getline(gtexData, line);

	multimap<string,string> tissueSampleMap;

	for (unsigned int i = 0; i < samplesNum; i++) {
		getline(gtexData, line);

		vector<string> tokens = splitTSV(line);

		tissueSampleMap.insert(pair<string, string>(tokens[6], tokens[0]));
	}

	for (auto sample : tissueSampleMap)
		cout << sample.first << " >>>> " << sample.second << endl;

	return 0;
}

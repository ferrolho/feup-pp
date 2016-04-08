#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "utilities.h"

using namespace std;

struct tissueFile_t {
	vector<string> genes;
	vector<vector<double>> values;
};

double calcPearson(const vector<double>& x, const vector<double>& y) {
	assert(x.size() == y.size());

	double n = x.size();

	double sumXY = 0;
	double sumX = 0, sumY = 0;
	double sumXX = 0, sumYY = 0;

	for (unsigned int i = 0; i < n; i++) {
		//numerator
		sumXY += x[i] * y[i];

		sumX += x[i];
		sumY += y[i];

		// denominator
		sumXX += x[i] * x[i];
		sumYY += y[i] * y[i];
	}

	/*
	* Taken from:
	* 	https://upload.wikimedia.org/math/b/c/7/bc7fa889f31ddbec0a05df656de340a5.png
	*/

	double numerator = n * sumXY - sumX * sumY;
	double denominator = sqrt(n * sumXX - sumX * sumX) * sqrt(n * sumYY - sumY * sumY);

	return denominator == 0 ? 0 : numerator / denominator;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Error: Too few arguments" << endl;
		return 1;
	}

	ifstream tissueFileIn;
	tissueFileIn.open(argv[1]);

	string line;

	// discarding useless info
	getline(tissueFileIn, line);
	getline(tissueFileIn, line);
	getline(tissueFileIn, line);

	tissueFile_t tissueFile;

	while (getline(tissueFileIn, line)) {
		vector<string> lineTokens = splitTSV(line);

		// save gene name
		tissueFile.genes.push_back(lineTokens[0]);

		// save gene data
		vector<double> valuesRow;

		for (unsigned int i = 1; i < lineTokens.size(); i++)
			valuesRow.push_back(stod(lineTokens[i], nullptr));

		tissueFile.values.push_back(valuesRow);
	}

	tissueFileIn.close();

	cout << "Pearson: " << calcPearson(tissueFile.values[0], tissueFile.values[1]) << endl;

	return 0;
}

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
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
	if (argc < 3) {
		cerr << "Error: Too few arguments" << endl;
		return 1;
	}

	/*
	* Read tissue file
	*/
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

	/*
	* Map tissue gene name to data row
	*/
	map<string, int> geneToRow;
	for (unsigned int i = 0; i < tissueFile.genes.size(); i++)
		geneToRow[tissueFile.genes[i]] = i;

	/*
	* Read mitocondrial genes list
	*/
	ifstream mitocondrialGenesFileIn;
	mitocondrialGenesFileIn.open(argv[2]);

	vector<string> mitocondrialGenes;

	while (getline(mitocondrialGenesFileIn, line))
		mitocondrialGenes.push_back(line);

	mitocondrialGenesFileIn.close();

	/*
	* Calculate correlations
	*/
	ofstream allCorrelationsOut, posCorrelationsOut, negCorrelationsOut;
	allCorrelationsOut.open("../data/output/correlations-output/Bladder-all.txt");
	posCorrelationsOut.open("../data/output/correlations-output/Bladder-pos.txt");
	negCorrelationsOut.open("../data/output/correlations-output/Bladder-neg.txt");

	int progress = 0;

	for (const auto& mitocondrialGene : mitocondrialGenes) {
		for (const auto& tissueGene : tissueFile.genes) {
			double pearson = calcPearson(tissueFile.values[geneToRow[mitocondrialGene]], tissueFile.values[geneToRow[tissueGene]]);

			ostringstream outputStream;

			outputStream << mitocondrialGene << " " << tissueGene << " " << pearson << endl;

			allCorrelationsOut << outputStream.str();

			if (pearson > 0.7)
				posCorrelationsOut << outputStream.str();
			else if (pearson < -0.7)
				negCorrelationsOut << outputStream.str();
		}

		printf("\rProgress: %5.1f %%", (++progress) * 100.0 / mitocondrialGenes.size());
		fflush(stdout);
	}

	allCorrelationsOut.close();

	cout << endl << "Done!" << endl;

	return 0;
}

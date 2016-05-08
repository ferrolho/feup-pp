#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include <sqlite3.h>

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

string quoteSQL(const string& s) {
	return string("'") + s + string("'");
}

void runSQL(const string& statement, sqlite3* db) {
	sqlite3_stmt* stmt;

	//preparing the statement
	sqlite3_prepare(db, statement.c_str(), -1, &stmt, NULL);

	//executing the statement
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

/**
*
* Compile:
*  g++ correlationsToDB.cpp -o correlationsToDB.out -Wall -lsqlite3 -std=c++11
*
* Usage:
*  ./correlationsToDB.out <tissue name> <mitocondrial genes list>
*
* Example:
*  ./correlationsToDB.out Bladder ../data/input/mitocondrialGenes.list
*
*/
int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: Too few arguments" << endl;
		return 1;
	}


	/*
	* Read mitocondrial genes list
	*/
	ifstream mitocondrialGenesFileIn;
	mitocondrialGenesFileIn.open(argv[2]);

	string tempGene;
	vector<string> mitocondrialGenes;

	while (getline(mitocondrialGenesFileIn, tempGene))
		mitocondrialGenes.push_back(tempGene);

	mitocondrialGenesFileIn.close();


	/*
	* Read tissue file
	*/
	string tissueName = argv[1];

	ifstream tissueFileIn;
	tissueFileIn.open("../data/output/tissues-output/" + tissueName + ".txt");

	cout << tissueName << " ... " << "Loading" << flush;

	if (tissueFileIn.is_open()) {
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


		/*
		* Map tissue gene name to data row
		*/
		map<string, int> geneToRow;
		for (unsigned int i = 0; i < tissueFile.genes.size(); i++)
			geneToRow[tissueFile.genes[i]] = i;


		/*
		* Calculate correlations
		*/
		sqlite3* db;

		if (sqlite3_open("../../coexpr/database/database.sqlite", &db) == SQLITE_OK) {
			int progress = 0;

			for (const auto& mitocondrialGene : mitocondrialGenes) {
				for (const auto& tissueGene : tissueFile.genes) {
					// skip self-correlation
					if (mitocondrialGene == tissueGene)
						continue;

					double pearson = calcPearson(tissueFile.values[geneToRow[mitocondrialGene]], tissueFile.values[geneToRow[tissueGene]]);

					stringstream ss;
					ss << "INSERT INTO correlations (gene1, gene2, correlation) VALUES ("
					<< quoteSQL(mitocondrialGene) << ", "
					<< quoteSQL(tissueGene) << ", "
					<< pearson << ");";

					runSQL(ss.str(), db);
				}

				printf("\r%s ... %5.1f %%", tissueName.c_str(), (++progress) * 100.0 / mitocondrialGenes.size());
				fflush(stdout);

				break;
			}

			cout << "\r" << tissueName << " ... OK!    " << endl;

			sqlite3_close(db);
		} else {
			cerr << endl << "ERROR: Failed to open DB." << endl;
		}
		
		tissueFileIn.close();
	} else {
		cerr << endl << "ERROR: Could not open file of tissue: " << tissueName << endl;
	}

	cout << "- All done! -" << endl;

	return 0;
}

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

const unsigned int BUFFER_SIZE = 256;

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

void resetTableDB(const string& tableName, sqlite3* db) {
	string statement;

	// drop table
	statement = "DROP TABLE IF EXISTS " + tableName;

	sqlite3_exec(db, statement.c_str(), nullptr, nullptr, nullptr);

	// create table
	statement = "CREATE TABLE \"" + tableName + "\" ("
	"\"id\" integer not null primary key autoincrement,"
	"\"gene1\" varchar not null,"
	"\"gene2\" varchar not null,"
	"\"correlation\" float not null)";

	sqlite3_exec(db, statement.c_str(), nullptr, nullptr, nullptr);
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
		* Open DB
		*/
		sqlite3* db;

		if (sqlite3_open("../../coexpr/database/database.sqlite", &db) == SQLITE_OK) {
			resetTableDB("correlations", db);

			sqlite3_stmt* stmt;
			sqlite3_prepare_v2(db, "INSERT INTO correlations VALUES (NULL, @gene1, @gene2, @correlation)", BUFFER_SIZE, &stmt, nullptr);

			int progress = 0;

			/*
			* Calculate correlations
			*/
			for (const auto& mitocondrialGene : mitocondrialGenes) {
				sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr);

				for (const auto& tissueGene : tissueFile.genes) {
					// skip self-correlation
					if (mitocondrialGene == tissueGene)
						continue;

					double pearson = calcPearson(tissueFile.values[geneToRow[mitocondrialGene]], tissueFile.values[geneToRow[tissueGene]]);

					ostringstream ss;
					ss << pearson;

					sqlite3_bind_text(stmt, 1, mitocondrialGene.c_str(), -1, SQLITE_TRANSIENT);
					sqlite3_bind_text(stmt, 2, tissueGene.c_str(), -1, SQLITE_TRANSIENT);
					sqlite3_bind_text(stmt, 3, ss.str().c_str(), -1, SQLITE_TRANSIENT);

					sqlite3_step(stmt);

					sqlite3_clear_bindings(stmt);
					sqlite3_reset(stmt);
				}

				sqlite3_exec(db, "END TRANSACTION", nullptr, nullptr, nullptr);

				printf("\r%s ... %5.1f %%", tissueName.c_str(), (++progress) * 100.0 / mitocondrialGenes.size());
				fflush(stdout);
			}

			cout << "\r" << tissueName << " ... OK!    " << endl;

			sqlite3_finalize(stmt);
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

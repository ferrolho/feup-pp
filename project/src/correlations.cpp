#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

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

int main() {
	vector<vector<double>> values = {{1,2,3,4}, {5,6,7,8}};

	for (auto row : values){
		for (auto elem: row)
			cout << elem << " ";

		cout << endl;
	}

	cout << "Pearson: " << calcPearson(values[0], values[1]) << endl;

	return 0;
}

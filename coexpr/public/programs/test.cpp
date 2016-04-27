#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream fout;
	fout.open("output.txt");

	if (fout.is_open()) {
		fout << "Hello, World!" << endl;
	} else {
		cerr << "Error: could not open output file." << endl;
	}

	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "ppm.h"
#include "Image.h"
#include "FilterLinear.h"
#include "FilterGamma.h"

using namespace std;

void exitProgram();
bool isNum(const std::string& s);

int main(int argc, char *argv[]) {
	if (argc <= 2) {
		if (argc == 1)
			cout << "No filename given, exiting..";
		exit(EXIT_FAILURE);
	}
	string fName(argv[argc -1]);
	
	cout << "(+)Opened file: " << fName << endl;

	FilterLinear fLinear;
	fLinear.params.resize(6);
	FilterGamma fGamma;
	fGamma.params.resize(1);

	imaging::Image f;
	if (!f.load(fName, "ppm")) {
		cout << "(-)A problem occurred while reading the file, exiting..";
		exit(EXIT_FAILURE);
	}

	int pointer = (argc > 1) ? 1 : 0; //for argv[1]


	while (pointer != 0) { //Every single filter
		if (strcmp(argv[pointer], "-f") != 0) {
			//Syntax error
			exitProgram();
		}

		if (strcmp(argv[++pointer], "linear") == 0) {
			//Linear filter
			for (int i = 1; i <= 6; i++) { //6 arguments

				if (!isNum(argv[pointer + i])) {
					exitProgram();
				}

				fLinear.params[i - 1] = atof(argv[pointer + i]);
			}
			//execute filter
			cout << "-Applying Filter Linear with values: ";
			for (int i = 1; i <= 6; i++) {
				cout << fLinear.params[i - 1] << " ";
			}
			cout << endl;
			f = fLinear << f;
			pointer += 7;
			if (argc <= pointer + 1)
				pointer = 0;

		} else if (strcmp(argv[pointer], "gamma") == 0) {
			//Gamma filter

			if (!isNum(argv[pointer + 1]))
				exitProgram();

			fGamma.params[0] = atof(argv[pointer + 1]);
			if (fGamma.params[0] < 0.5 || fGamma.params[0]>2) {
				cout << "(-)Filter gamma acceptable values: [0.5, 2]";
				exit(EXIT_FAILURE);
			}
			//execute filter
			cout << "-Applying Filter Gamma with value: " << fGamma.params[0] << endl;
			f = fGamma << f;
			pointer +=2;
			if (argc <= pointer + 1)
				pointer = 0;
		}
	}


	if (!f.save("filtered_" + fName, "ppm"))
		cout << "(-)A problem occurred while saving the file.";
	else
		cout << "\a(+)Saved file with name: filtered_" + fName << endl;
	system("pause");



	return 0;
}

void exitProgram() {
	cout << "(-)There is a syntax error in arguments, exiting.." << endl;
	system("pause");
	exit(EXIT_FAILURE);
}
bool isNum(const std::string& s) {
	std::string::const_iterator it = s.begin();
	int point = 0;
	int count = 0;
	while (it != s.end() && (isdigit(*it) || (*it == '.' && point == 0) || (*it=='-' && count++ == 0))) {
		if (*it == '.')
			point++;
		it++;
	}
	return !s.empty() && it == s.end();
}
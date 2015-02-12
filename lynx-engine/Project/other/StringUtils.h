#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using std::string;
using std::cin;
using std::getline;
using std::cout;
using std::endl;
using std::fixed;
using std::stringstream;
using std::setprecision;

namespace StringUtils {
	void print(string s);
	void printl(string s);
	string getInput(void);
	string toString(double num, int decimalPlaces);
	string toString(double num);
	string toString(int num);
}

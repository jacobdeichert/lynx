#include "StringUtils.h"

void StringUtils::print(string s) {
	cout << s;
}

void StringUtils::printl(string s) {
	cout << s << endl;
}


string StringUtils::getInput(void) {
	string s;
	getline(cin, s);
	return s;
}

string StringUtils::toString(double num, int decimalPlaces) {
	stringstream ss;
	ss << fixed << setprecision(decimalPlaces); // enables a fixed precision of decimal places
	ss << num;
	return ss.str();
}

string StringUtils::toString(double num) {
	stringstream ss;
	ss << num;
	return ss.str();
}

string StringUtils::toString(int num) {
	stringstream ss;
	ss << num;
	return ss.str();
}
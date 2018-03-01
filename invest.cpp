#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include "decl.h"

using namespace std;

const string USAGE = "Usage: Invest [--initialAmount ?] --monthlyAmount ? --months ? --annualRate ? [--tax true/false]";

template<class T> bool contains(const T&, const vector<T>& v);

template<class T> bool containsAll(const vector<T>& vContained, const vector<T>& vContains);

map<string, double> createArgsMap(int, char**);

/**
args: [--initialAmount ?] --monthlyAmount ? --months ? --annualRate ? [--tax true/false]
*/
int main(int argc, char** argv) 
{
	map<string, double> mArgs = createArgsMap(argc, argv);
	InvestmentCalculator(mArgs).calculate();
}


map<string, double> createArgsMap(int argc, char** argv) {

	const vector<string> ARG_NAMES = {"--initialAmount", "--monthlyAmount", "--months", "--annualRate", "--tax"};
	const vector<string> REQUIRED_ARG_NAMES = {"--monthlyAmount", "--months", "--annualRate"};

	if (argc > 1 && argv[1] == "--prompt") {

	} else {
		// ignore first arg, which is program name
		int argsCount = argc - 1;
		if (argsCount == 0 || argsCount % 2 != 0)
			throw runtime_error(USAGE); 
	}

	map<string, double> result;
   	vector<string> keys;
	// ignore first arg, which is program name
	for (int i = 1; i < argc; i += 2) {
		string name = argv[i];
		keys.push_back(name);
		double value = atof(argv[i + 1]);
		result[name] = value;
	}

	if (!containsAll(keys, ARG_NAMES)) 
		throw runtime_error(USAGE);

	if (!containsAll(REQUIRED_ARG_NAMES, keys))
		throw runtime_error("Missing required arguments. " + USAGE);
	
	return result;
}

template<class T> bool contains(const T& item, const vector<T>& v) 
{
	return !v.empty() && find(v.begin(), v.end(), item) != v.end();
}

template<class T> bool containsAll(const vector<T>& vContained, const vector<T>& vContains) 
{
	if (vContained.empty() || vContains.empty())
		return false;

	/* assuming unique objects for each vector */
	if (vContained.size() > vContains.size())
		return false;

	for (int i = 0; i < vContained.size(); i++) {
		T item = vContained[i];
		if (find(vContains.begin(), vContains.end(), item) == vContains.end())
			return false;
	}

	return true;
}
  



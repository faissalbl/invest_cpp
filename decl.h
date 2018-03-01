#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Application {
	public:
	int monthApplied;
	double amount;
	Application(int monthApplied, double amount) 
		:monthApplied(monthApplied), amount(amount) {}
};

class InvestmentCalculator {

	private:
		map<string, double> mArgs;
		double calculateTax(int);
		template<class T> T& nvl(const T&, const T&);
  
	public:
		InvestmentCalculator(map<string, double> mArgs)
			:mArgs(mArgs) {}
  
		void calculate();  
};



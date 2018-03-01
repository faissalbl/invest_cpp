#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include "decl.h"

using namespace std;

void InvestmentCalculator::calculate() {
	const int MONTHS_IN_YEAR = 12;
	const int MONTH_ZERO = 0;
	const int ONE = 1;

  	double initialAmount = mArgs["--initialAmount"];
	double monthlyAmount = mArgs["--monthlyAmount"];
	int months = int(mArgs["--months"]);
	double annualRate = mArgs["--annualRate"];

	vector<Application> applications;

	applications.push_back(Application(MONTH_ZERO, initialAmount));

	if (monthlyAmount > 0)
		for (int month = 1; month <= months; ++month) {
			applications.push_back(Application(month, monthlyAmount));
		}

	double totalAmount = 0.0;
	double totalCorrectedAmount = 0.0;
	double totalTaxAmount = 0.0;
	for(Application& application : applications) {

		int applicationMonths = months - application.monthApplied;
		int applicationYears = applicationMonths / MONTHS_IN_YEAR;
		int remainingMonths = applicationMonths % MONTHS_IN_YEAR;

		cout << "applicationMonths " << applicationMonths << endl;
		double tax = calculateTax(applicationMonths);
		cout << "tax " << tax << endl;
		
		totalAmount += application.amount;

		double amount = application.amount;

		if (applicationYears > 0) 
			amount = application.amount * pow((1 + annualRate), applicationYears);

		cout << "annualRate " << (1 + annualRate) << endl;
		cout << "years " << applicationYears << endl;
		cout << "amountYears " << amount << endl;

		cout << "remainingMonths " << remainingMonths << endl;
		if (remainingMonths > 0) {
			double amountYear = amount * (1 + annualRate);
			double grossProfitYear = amountYear - amount;
			cout << "grossProfitYear " << grossProfitYear << endl;
			double grossProfitPerMonth = grossProfitYear / MONTHS_IN_YEAR;
			cout << "grossProfitPerMonth " << grossProfitPerMonth << endl;
			double grossProfitMonths = grossProfitPerMonth * remainingMonths;
			cout << "grossProfitMonths " << grossProfitMonths << endl;
			amount += grossProfitMonths;
		}

		double grossProfit = amount - application.amount;
		cout << "grossProfit " << grossProfit << endl;

		totalCorrectedAmount += amount;

		cout << "taxableAmount " << grossProfit << endl;
		double taxAmount = grossProfit * tax;
		cout << "taxAmount " << taxAmount << endl;
		cout << "------------------------------------------" << endl;
		totalTaxAmount += taxAmount;
	}
	double netAmount = totalCorrectedAmount - totalTaxAmount;

	cout << "Initial Amount:\t" << initialAmount << endl;    
	cout << "Months:\t" << months << endl;
	cout << "Invested Amount:\t" << totalAmount << endl;
	cout << "Corrected Amount:\t" << totalCorrectedAmount << endl;
	cout << "Tax Amount:\t" << totalTaxAmount << endl;
	cout << "Net Amount:\t" << netAmount << endl;	
}

//TODO verify real taxes for periods
double InvestmentCalculator::calculateTax(int month) {
	const double INITIAL_TAX = 0.225;

	const int LIMIT_1 = 6;
	const int LIMIT_2 = 12;
	const int LIMIT_3 = 24;
	
	const double TAX_1 = 0.2;
	const double TAX_2 = 0.185;
	const double TAX_3 = 0.15;

	if (month < LIMIT_1) return INITIAL_TAX;
	if (month < LIMIT_2) return TAX_1;
	if (month < LIMIT_3) return TAX_2;
	return TAX_3; 		
}
  
template<class T> T& InvestmentCalculator::nvl(const T& arg, const T& defaultArg) {
	if (arg == NULL)
		return defaultArg;

	return arg;
}


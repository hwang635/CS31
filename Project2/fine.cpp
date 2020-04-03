//Project 2: Calculating fine for college admissions fraud

#include <iostream>
#include <string>
using namespace std;

int main() {

	string defendantName;
	double amountPaid;
	string athleteStatus;
	double fine = 20.0;

	//Gets input for defendant's information
	cout << "Defendant: ";
	getline(cin, defendantName);
	cout << "Amount paid (in thousands): ";
	cin >> amountPaid;
	cin.ignore(10000, '\n');
	cout << "Fake athlete? (y/n): ";
	getline(cin, athleteStatus);
	cout << "---" << endl;

	//Checks if there is an input error. If no input error, calculates and outputs fine.
	if (defendantName == "")
		cout << "You must enter a defendant name." << endl;
	else if (amountPaid < 0)
		cout << "The amount paid must not be negative." << endl;
	else if(athleteStatus != "y" && athleteStatus != "n") //if the string isn't y and isn't n
		cout << "You must enter y or n." << endl;
	else  {
		//Calculates the defendant's fine
		if (amountPaid <= 40) //calc fine for amount paid under 40k
			fine += 0.66 * amountPaid;
		else if (amountPaid > 40.0 && amountPaid <= 250.0) { //calc fine for amount paid btw 40 and including 250
			fine += 0.66 * 40.0;
			if (athleteStatus == "n") //defendant didn't fake being an athlete
				fine += 0.1 * (amountPaid - 40.0);
			else //defendant did fake being an athlete
				fine += 0.22 * (amountPaid - 40.0);
		}
		else {//calc amount paid over 250 thousand
			fine += 0.66 * 40.0;
			if (athleteStatus == "n") //defendant didn't fake being an athlete
				fine += 0.1 * (210.0);
			else //defendant did fake being an athlete
				fine += 0.22 * (210.0);
			fine += 0.14 * (amountPaid - 250.0); //fine for over 250k
		}

		//Outputs fine as number with one number after the decimal point
		cout.setf(ios::fixed);
		cout.precision(1);
		cout << "The suggested fine for " << defendantName << " is $" << fine << " thousand." << endl;
	}
	
}
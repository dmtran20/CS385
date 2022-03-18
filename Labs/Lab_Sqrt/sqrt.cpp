/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Dylan Tran
 * Version : 1.0
 * Date    : September 2, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

double sqrt(double num, double epsilon){
	//make first guess be the number
	double last_guess = num;
	double next_guess = (last_guess+num / last_guess) / 2.0;


	if (num < 0.0){
		return numeric_limits<double>::quiet_NaN();
	}
	if (num==0.0 || num == 1.0){
		return num;
	}

	while (epsilon < abs(last_guess - next_guess)){
		last_guess = next_guess;
		next_guess = (last_guess+ num / last_guess) / 2.0;
	}

	return next_guess;
}

int main(int argc, char*argv[]){

	double num;
	double epsilon=1e-7;

	if (argc < 2){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	if (argc > 3){
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;

	}
	istringstream iss;
	iss.str(argv[1]);
	if(!(iss >> num)){
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	iss.clear();

	//opt epilison if there, or if it is not there.
	if (argc == 3){
		iss.str(argv[2]);
		if(!(iss >> epsilon)){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		if (0 >= epsilon){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;

		}

	}
	cout << fixed << setprecision(8) << sqrt(num, epsilon) <<endl;
	return 0;


}


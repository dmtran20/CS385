/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :Dylan Tran
 * Date        :9/15/2021
 * Description : Sieve of Eratosthenes
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();

}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document
	const int max_prime_width = num_digits(max_prime_),primes_per_row = 80 / (max_prime_width + 1);
	int primes_to_right;
	primes_to_right=primes_per_row;
	for (int i = 2; i <= limit_; i++){
		if (primes_to_right == 0){
			primes_to_right = primes_per_row;
			cout << endl;
		}
		//If the number is prime
		if (is_prime_[i] == true){
			if (primes_to_right != primes_per_row){
				cout << " ";
			}

		if (primes_per_row < num_primes()){
			cout << setw(max_prime_width) << i;
		}
		else {
			cout << i;
		}
		primes_to_right--;
		}
	}
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int Num_of_primes;
	for (int i = 2; i<= limit_; i++){
		if (is_prime_[i]== true){
			Num_of_primes++;

		}
	}

    return Num_of_primes;
}

void PrimesSieve::sieve() {
	//num_primes_= count_num_primes();
	// TODO: write sieve algorithm
	for (int i = 0; i <=limit_; i++){
		is_prime_[i]=true;

	}
	is_prime_[0] = false;
	is_prime_[1] = false;
	for (int i = 2; i <=sqrt(limit_); i++){
		if (is_prime_[i]== true){
			for (int j = i*i; j<=limit_; j=j+i){
				is_prime_[j] = false;
			}
		}
	}
	for(int i = 2; i < limit_+1 ; i++){
		is_prime_[i] ? max_prime_ = i: max_prime_;
	}
	num_primes_= count_num_primes();


}







int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int num_of_digits=1;
	while (num/10 > 0){
		num=num/10;
		num_of_digits++;

	}
    return num_of_digits;
}

int main() {

    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieveT(limit);
    cout << endl << "Number of primes found: " << sieveT.num_primes()<< endl;
    cout << "Primes up to " <<limit << ":"<<endl;
    sieveT.display_primes();

    return 0;
}

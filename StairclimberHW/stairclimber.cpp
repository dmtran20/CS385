/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Dylan Tran
 * Date        : 10/2/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector <vector<int>> num_ways;
	if (num_stairs <= 0){
		num_ways.push_back({});
	}
	else{
		for (int i=1; i<4; i++){
			if (num_stairs >= i){
				vector<vector<int>> temp = get_ways(num_stairs-i);
				for (size_t j=0; j <temp.size(); j++){
					temp[j].insert(temp[j].begin(), i);
				}
				num_ways.insert(num_ways.end(), temp.begin(), temp.end());
			}

		}

	}
	
	return num_ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	if (ways.size() > 1){
		cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
	}
	if (ways.size() == 1){
		cout << ways.size() << " way to climb " << "1 stair." << endl;
	}

	int indent = 0;
	

	for (size_t i=0; i <ways.size(); i++){
		if (ways.size()>=10){
			indent = 1;
		}
		cout << setw(indent+1) << i+1 << ". ";
		cout << "[";
		for(size_t j=0; j<ways[i].size(); j++){
			if (j != ways[i].size()-1){
				cout << ways[i][j] << ", ";
			}
			else {
				cout << ways[i][j];

			}
		}
		cout << "]" << endl;
	}

}

int main(int argc, char * const argv[]) {
	int stairs;
	if (argc < 2){		
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
    }
	if (argc > 2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
    }
	istringstream iss(argv[1]);
    if (!(iss  >> stairs)){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
	}
	else if (stairs < 1){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
	}
	else {
		vector<vector<int>> num_ways=get_ways(stairs);
		display_ways(num_ways);
	}
	return 0; 


}

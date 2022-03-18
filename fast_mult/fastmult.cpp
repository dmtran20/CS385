/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Dylan Tran
 * Date        : 12/1/2021
 * Description : 
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <limits>
#include <iomanip> 

using namespace std;

long INF=numeric_limits<unsigned int>::max();
int num_vertices;
long** dis_matrix;



long** Floyd(long** const matrix){
	//Implements Floyd’s algorithm for the all-pairs shortest-paths problem
	//Input: The weight matrix W of a graph with no negative-length cycle
	//Output: The distance matrix of the shortest paths’ lengths 
	for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++){
            dis_matrix[i][j] = matrix[i][j];
		}
	}

	for (int k=0; k<num_vertices ;k++){
		for (int i=0; k<num_vertices; i++){
			for (int j=0; j<num_vertices; j++){
				if (dis_matrix[i][j] > dis_matrix[i][k] + dis_matrix[k][j] && (dis_matrix[i][k] !=INF && dis_matrix[k][j])){
					dis_matrix[i][j]= dis_matrix[i][k]+dis_matrix[k][j];
				}
			}
		}
	}
	return dis_matrix;

}

int len(int value) {
	int length;
	while (value >=10){
		value /= 10;
		length++;
	}
	return length;
}




/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? len(max_val) :
	len(max(static_cast<long>(num_vertices), max_val));
	
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}




int main(int argc, const char *argv[]) {
	
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    int numVert;
	
	string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
			istringstream iss;
			iss.str(line);
			if (line_number == 1){
				if (!(iss >>numVert)){
					cerr << "Error: Invalid number of vertices '" << line << "' on line" << " 1." << endl;
					return 0;
				}
				else if (numVert <= 0 || numVert > 26){
					cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
					return 0;
				}
			}
			
			else{
				vector<string> each_line;
				int line_content=0;
				for (string line; iss >> line;){
					each_line.push_back(line);
					line_content++;
				}
				if (line_content != 3){
					cerr << "Error: Invalid edge data '"<< line << "' on line " << line_number << "." << endl;
					return 1;
				}
				
				else if (each_line.at(0).size() > 1){
					cerr << "Error: Starting vertex '"<< each_line.at(0) << "' on line " << line_number << " is not among valid values " << "A" << "-" << char(num_vertices+64)<< "." << endl;
					return 1;
				}
				else if (each_line.at(1).size() > 1){
					cerr << "Error: Ending vertex '"<< each_line.at(1) << "' on line " << line_number << " is not among valid values " << "A" << "-" << char(num_vertices+64)<< "." << endl;
					return 1;
				}
			}
			
            //cout << line_number << ":\t" << line << endl;
            ++line_number;
			
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}


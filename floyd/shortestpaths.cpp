/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Ron Dumalagan and Dylan Tran
 * Version     : 1.0
 * Date        : 12/04/2021
 * Description : Implementation of Floyd's algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <climits>

#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

// things that I had to make global variables or else this wouldn't work
int num_vertices;
long INF = LONG_MAX;
long** matrix;
long** floyds;
long** intermediate;



// initialize matrix with 0s and INFs
long** init_matrix(int num_vertices) {
    long** matrix = new long*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        matrix[i] = new long[num_vertices];
    }
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = INF;
            }
        }
    }
    return matrix;
}

// initialize intermediate matrix with INFs
long** init_intermediate(int num_vertices) {
    long** m = new long*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        m[i] = new long[num_vertices];
    }
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            m[i][j] = INF;
        }
    }
    return m;
}

// helper function for display_table()
int len(long n){
    int length = 0;
    while (n != 0){
        n = n / 10;
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
        if (label.compare("Intermediate vertices:") == 0 && num_vertices == 1) {
            cout << setw(max_cell_width + 1) << " " << static_cast<char>(j + 'A');
        }
        else {
            cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
        }
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

void update_intermediate(long** intermediate_matrix, int i, int j, int k){
    intermediate[i][j] = k;
}



long** floyd (long** distance_matrix) {
    long** path_lengths = distance_matrix;
    intermediate= init_intermediate(num_vertices);
    for (int k = 0; k < num_vertices; k++) {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if((distance_matrix[i][k] != INF && distance_matrix[k][j] != INF) && (distance_matrix[i][j] > (distance_matrix[i][k] + distance_matrix[k][j]))) {
                    path_lengths[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                    // update intermediate array with value of 'k' in intermediate[i][j]
                    update_intermediate(intermediate, i, j, k);
                }
            }
        }
    }
    return path_lengths;
}

string backtrack(int start, int end, long** matrix, long** intermediate){
	string path_temp ="";
	if (matrix[start][end]==INF){
		return "none";

	}
	if (intermediate[start][end] == INF){
		path_temp.push_back(char('A'+start));
		path_temp.push_back(char('A'+end));
		return path_temp;
	}
	else{
		//including every edge
		path_temp=(backtrack(start, intermediate[start][end], matrix, intermediate));
		path_temp.append(backtrack(intermediate[start][end], end, matrix, intermediate).substr(1));
		
		return path_temp;
	}
}


void display_i_paths(long** matrix, long** intermediate){
	//distance matrix needed
	string arrow = " -> ";
	//long result;
	for (int i =0; i < num_vertices; i++){
		for (int j=0; j<num_vertices;j++){
			string path="";
			long distance =matrix[i][j];

			//if distance matrix ==inf  and they are not equal there is not path
			if(i != j && matrix[i][j] == INF){
				path="none";
				cout << static_cast<char>('A' + i) << arrow << static_cast<char>('A' + j) << ", distance: " << "infinity, " << "path: " << path;
			}
			//if they are equal the path =itself
			else if(i == j){
				path = static_cast<char>('A' + i);
				cout << static_cast<char>('A' + i) << arrow << static_cast<char>('A' + j) << ", distance: " << distance << ", path: " << path;
			}
			else {
				
				path=(backtrack(i, j, matrix, intermediate));
				//path is incorrectly only holding start and end values
				cout << static_cast<char>('A' + i) << arrow << static_cast<char>('A' + j) << ", distance: " << distance << ", path: " << path[0];
				for (unsigned int i =1; i < path.length();i++){
					cout << arrow << path[i];
				}
			}
			cout << endl;
		
		}
	}

}

int main(int argc, char *argv[]) {
    // initialize stuff
    istringstream iss;
    int edge_weight;
    string temp, vertex1, vertex2;

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
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        while (getline(input_file, line)) {
            iss.str(line);
            // remove '\r' from end of line if there (sometimes getline() returns strings ending in '\r' for some reason)
            if (!line.empty() && line[line.size() - 1] == '\r'){
                line.erase(line.size() - 1);
            }
            // if first line:
            if (line_number == 1) {
                // Error: The number of vertices is not an integer between 1 and 26.
                if (!(iss >> num_vertices) || (num_vertices < 1 || num_vertices > 26)) {
                    cerr << "Error: Invalid number of vertices '"<< line << "' on line 1." << endl;
                    return 1;
                }
                iss >> num_vertices;
                matrix = init_matrix(num_vertices);
                ++line_number;
                iss.clear();
            }
            // if not first line:
            else{
                // Error: Each line should have three components.
                int num_inputs = 0;
                while (iss >> temp) {
                    num_inputs++;
                }
                if (num_inputs != 3) {
                    cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                
                // reload stream
                iss.clear();
                iss.str(line);
                iss >> vertex1;
                iss >> vertex2;
                char v1char = vertex1[0];
                char v2char = vertex2[0];
                // Error: The starting vertex must be in range.
                if (vertex1.length() != 1 || v1char < 'A' || v1char > 'A' + num_vertices - 1) {
                    cerr << "Error: Starting vertex '" << vertex1 << "' on line " << line_number << " is not among valid values A-" << static_cast<char>('A' + num_vertices - 1) << "." << endl;
                    return 1;
                }
                // Error: The ending vertext must be in range.
                if (vertex2.length() != 1 || v2char < 'A' || v2char > 'A' + num_vertices - 1) {
                    cerr << "Error: Ending vertex '" << vertex2 << "' on line " << line_number << " is not among valid values A-" << static_cast<char>('A' + num_vertices - 1) << "." << endl;
                    return 1;
                }
                // Error: Edge weight must be a positive integer.
                if (!(iss >> edge_weight)) {
                    iss >> temp;
                    cerr << "Error: Invalid edge weight '" << temp << "' on line " << line_number << "." << endl;
                    return 1;
                }
                else if (edge_weight <= 0) {
                    cerr << "Error: Invalid edge weight '" << edge_weight << "' on line " << line_number << "." << endl;
                    return 1;
                }
                matrix[(int)v1char - 65][(int)v2char - 65] = edge_weight;
                ++line_number;
                iss.clear();
            }
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    display_table(matrix, "Distance matrix:");

    floyds = floyd(matrix);

    display_table(floyds, "Path lengths:");
	
	display_table(intermediate, "Intermediate vertices:", true);
	
	
	display_i_paths(floyds,intermediate);

    // delete matrices when done
    for (int i = 0; i < num_vertices; i++) {
        delete [] matrix[i];
        delete [] intermediate[i];
    }
    delete [] matrix;
    delete [] intermediate;

    return 0;

}
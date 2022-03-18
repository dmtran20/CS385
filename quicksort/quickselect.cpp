/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        :Dylan Tran
 * Pledge        :I pledge my Honor that I have abided by the Stevens Honor System.
 * Date          :10/21/2021
 * Description   : Implements the quickselect algorithm.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;


size_t lomuto_partition(int array[], size_t left, size_t right) {
    // TODO
    // DO NOT change the function header in any way.
    int p=array[left];
    int s=left;
    for (size_t i=left+1; i<=right; i++){
        if (array[i]<p){
            s=s+1;
            swap(array[s], array[i]);
            }
    }
    swap (array[left],array[s]);
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    // TODO
    // DO NOT change the function header in any way.
    size_t size=lomuto_partition(array, left, right);
    //if the size is at the smallest element return that value
    if (size == k-1){
        return array[size];    
        }
    //If the left and right are the same, return that value
    if (left == right){
        return array[left];
        }
    //if size is greater than the smallest, keep left and recursive
    if (size > k-1){
        return quick_select(array, left, right-1, k);

    }
    else {
        return quick_select(array, left+1, right, k);
    }

    return 0;
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    
    // TODO - error checking k against the size of the input
    int *array=new int[num_values];
    for (int i=0; i < num_values; i++){
        array[i]=values[i];
    }
    int smallest_elem = quick_select(array, num_values, k);
    if (k > num_values){
        if (num_values > 1){
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " values."<<endl;
        }
        else {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value."<<endl;

        }
    }
    // TODO - call the quick_select function and display the result
    else{
        cout <<"Smallest element " << k <<": " <<smallest_elem << endl;
    }

    delete[] array;
    
    return 0;
}

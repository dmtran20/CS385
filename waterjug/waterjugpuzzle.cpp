/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Dylan Tran
 * Date        : 10/12/2021
 * Description :
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

int cap_A;
int cap_B;
int cap_C;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directionsvector;
    State *parent;


    State(int _a, int _b, int _c, vector<string> _directionsvector) :
        a{_a}, b{_b}, c{_c}, directionsvector{_directionsvector}, parent{nullptr} { }

    
    vector<string> get_directionvector(){
		return directionsvector;
	}
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
    void print_lines() {
		for (unsigned int i = 0; i < directionsvector.size(); ++i) {
			cout << directionsvector[i] << endl;
		}
	}

    
};

vector<string> create_initial(int a, int b, int c){
    vector<string> initial;
    stringstream iss;
    iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
    initial.push_back(iss.str());
    return initial;
}


bool Found = 0;

void BFS(int state_a, int state_b, int state_c, int goal_a, int goal_b, int goal_c){
    /*
    int rows = state_a+1;
    int col = state_b+1;
    bool **v_matrix = new bool* [rows];
    for(auto i = 0; i < rows; i++) {
        v_matrix[i] = new bool [col];
        fill(v_matrix[i], v_matrix[i]+col, 0);
        }
    queue<State> pours;

    State initial(state_a, state_b,state_c, create_initial(state_a,state_b,state_c));
    pours.push(initial);

    string line;
    while ((pours.size() != 0)){
        state_a=pours.front().a;
        state_b=pours.front().b;
        state_c=pours.front().c;

        if (state_a== goal_a && state_b == goal_b && state_c == goal_c){
            pours.front().print_lines();
            cout<<"HI" <<endl;
            Found=1;
            break;
        }
        State Front = pours.front();
        pours.pop();

        //Pour C to A
        if(state_a <cap_A){
            stringstream iss; 
            int ca= state_c+state_a;
            if (ca>state_a){
                state_a=cap_A;
            }
            //b doesn't change

            iss<< ca - state_a;
            if (ca-state_a >=2){
                line="Pour " + iss.str() + " gallons from C to A. ";
            }
            else{
                line="Pour " + iss.str() + " gallon from C to A. ";
            }
            if (!(v_matrix[state_a][state_b])){
                vector<string> path = Front.get_directionvector();
                path.push_back(line);
                State ca(state_a,state_b,state_c, path);
                pours.push(ca);

            }
        
        }
        //b to A
        if(state_a <cap_A){
            if (state_b !=0){
                stringstream iss; 
                int ab= state_b+state_a;
                if (ab>state_a){
                    state_a=cap_A;
                }
                int excess=ab-state_a;
                int ab2=state_b-(excess);
                if (ab2 < 0){
                    ab=0;
                }
				if (ab2 > cap_B){
                    ab2=cap_B;

                }
                iss<< state_b - ab2;
                if (state_b - ab2 >=2){
                    line="Pour " + iss.str() + " gallons from B to A. ";
                    }
                else{
                    line="Pour " + iss.str() + " gallon from B to A. ";
                    }
                if (!(v_matrix[state_a][state_b])){
                    vector<string> path = Front.get_directionvector();
                    path.push_back(line);
                    State ab(state_a,state_b,state_c, path);
                    pours.push(ab);

                        }
                    }
            }
        //Pour C to B
        if(state_b <cap_B){
            stringstream iss; 
            int b= state_c+state_b;
            if (b>cap_B){
                b =cap_B;
            }


            iss<< b - state_b;
            if (b-state_a >=2){
                line="Pour " + iss.str() + " gallons from C to B. ";
            }
            else{
                line="Pour " + iss.str() + " gallon from C to B. ";
            }
            if (!(v_matrix[state_a][state_b])){
                vector<string> path = Front.get_directionvector();
                path.push_back(line);
                State c(state_a,state_b,state_c, path);
                pours.push(c);

            }
        
        }
        //Pour A to B
        if(state_b <cap_B){
            if (state_a !=0){
                int a;
                stringstream iss; 
                int b= state_a+state_b;
                if (b>cap_B){
                    b=cap_B;
                    a=state_a-(b-state_b);
                }
                else {
                    state_a=0;
                    
                }
                if (state_a< 0){
                    state_a=0;
                }
				if (state_a<a){
                    state_a=cap_A;

                }
                iss<< state_b - b;
                if (state_b - b >=2){
                    line="Pour " + iss.str() + " gallons from A to B. ";
                    }
                else{
                    line="Pour " + iss.str() + " gallon from A to B. ";
                    }
                if (!(v_matrix[state_a][state_b])){
                    vector<string> path = Front.get_directionvector();
                    path.push_back(line);
                    State b(state_a,state_b,state_c, path);
                    pours.push(b);

                        }
                    }
            }
        //Pour B to C
        if(state_c <cap_C){
            if (state_b !=0){
                stringstream iss; 
                int cb= state_c+state_b;
                if (state_c>cap_C){
                    state_c=cap_C;
                }
                int bc=state_c-cb;
                if (state_b> cap_B){
                    state_b=state_c;
                }
				if (state_b<0){
                    state_b=0;

                }
                iss<< state_b - bc;
                if (state_b - bc >=2){
                    line="Pour " + iss.str() + " gallons from A to B. ";
                    }
                else{
                    line="Pour " + iss.str() + " gallon from A to B. ";
                    }
                if (!(v_matrix[state_a][state_b])){
                    vector<string> path = Front.get_directionvector();
                    path.push_back(line);
                    State cb(state_a,state_b,state_c, path);
                    pours.push(cb);

                        }
                    }
            }
            //A to C
        if(state_a+state_b <cap_C){
            if (state_a !=0){
                stringstream iss; 
                int ca= state_c+state_a;
                if (state_c>cap_C){
                    state_c=cap_C;
                }
                int a=state_a-(ca-state_c);
                if (a> cap_A){
                    a=cap_A;
                }
				if (a<0){
                    a=0;

                }
                iss<< state_a-a;
                if (state_a - a >=2){
                    line="Pour " + iss.str() + " gallons from A to C. ";
                    }
                else{
                    line="Pour " + iss.str() + " gallon from A to C. ";
                    }
                if (!(v_matrix[state_a][state_b])){
                    vector<string> path = Front.get_directionvector();
                    path.push_back(line);
                    State a(state_a,state_b,state_c, path);
                    pours.push(a);

                        }
                    }
            }

        
        }
    if (Found==0){
        cout << "No solution." <<endl;
        }
	return;
    */
   cout << "No solution." <<endl;

}

int main(int argc, char * const argv[]) {
    int jug_Array[6]={0,0,0,0,0,0}; //Create arry for all jugs
    if (argc!=7){
    	cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
    	return 1;
        }
    istringstream iss;
    for (int i=1; i <= 3; i++){
        iss.str(argv[i]);
        //see if jug is negative
        if (!(iss >> jug_Array[i-1]) ||(0 >= jug_Array[i-1])){
            if (i==1){
                cerr <<"Error: Invalid capacity '" << argv[i] << "' for jug A." <<endl;
                return 1;
                }
            if (i==2){
                cerr <<"Error: Invalid capacity '" << argv[i] << "' for jug B." <<endl;
                return 1;
                }
            if (i==3){
                cerr <<"Error: Invalid capacity '" << argv[i] << "' for jug C." <<endl;
                return 1;
                }
            }
        iss.clear();
        }
    for (int i=4; i <= 6; i++){
        iss.str(argv[i]);
        if (!(iss >> jug_Array[i-1]) || (0 > jug_Array[i-1])){
            if (i==4){
                cerr <<"Error: Invalid goal '" << argv[i] << "' for jug A." <<endl;
                return 1;
                }
            if (i==5){
                cerr <<"Error: Invalid goal '" << argv[i] << "' for jug B." <<endl;
                return 1;
                }
            if (i==6){
                cerr <<"Error: Invalid goal '" << argv[i] << "' for jug C." <<endl;
                return 1;
                }
            }
            iss.clear();
        }
        /* Want to try and see if jug A's goal is greater than whats inside the jug
        not working atm
        */
    for (int i=0; i<4; i++){
        iss.str(argv[i]);
        if (!(iss >> jug_Array[i-1]) || (0 >= jug_Array[i-1])){
            if (jug_Array[3] > jug_Array[0]){
            cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
            return 1;
        }
        if (jug_Array[4] > jug_Array[1]){
            cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
            return 1;
            }
        if (jug_Array[5] > jug_Array[2]){
            cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
            return 1;
            }
        }
    }
    int sum;
    //test if the goal's total gallons is greater than the capacity c
    for(int i=3; i<6; i++){
        sum+=jug_Array[i];
        }
    if (sum > jug_Array[2] || sum < jug_Array[2]){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    cap_A=jug_Array[0];
    cap_B=jug_Array[1];
    cap_C=jug_Array[2];
    BFS(0,0,jug_Array[3], jug_Array[4],jug_Array[5], jug_Array[6]);

    return 0;
    }





#include <bits/stdc++.h>
#define DEBUG false
#define endl "\n"

using namespace std;

int m, n, test_case = 0;
map<string, set<string> > friends;
vector<string> roll_numbers;
map<string, bool> is_sitting;
vector< vector<string> > classroom;
int seated = 0;
vector< vector<int> > fill_count;

typedef pair<int, int> NODE;

class CompareNode {
   public:
     bool operator() (const NODE &e1, const NODE &e2)
     {
         return e1.first > e2.first; // strict weak ordering required
     }
 };

void clear_global_vars(){
	friends.clear();
	roll_numbers.clear();
	is_sitting.clear();
	classroom.clear();
	seated = 0;
}

void check_input(){
	cout << "Case : " << test_case << endl << "Friend list is as follows: -" << endl;
	vector<string>::iterator roll;
	for(roll = roll_numbers.begin(); roll != roll_numbers.end(); ++roll){
		int friend_count = friends[*roll].size();
		cout << *roll << " " << friend_count << " ";
		set<string>::iterator itr = friends[*roll].begin();
		for(;itr != friends[*roll].end(); ++itr){
			cout << *itr << " ";
		}
		cout << endl;
	}
}

bool can_sit2(string &roll, int row, int col){
	if(DEBUG){
		cout << "trying " << roll << " on row = " << row << ", col = " << col << endl;
	}
	if(is_sitting[roll]){
		if(DEBUG){
			cout << "already seated\n";
		}
		return false;
	}
	int array[8][2];

	array[0][0] = row-1;
	array[0][1] = col-1;
	array[1][0] = row-1;
	array[1][1] = col;
	array[2][0] = row-1;
	array[2][1] = col+1;
	array[3][0] = row;
	array[3][1] = col+1;
	array[4][0] = row+1;
	array[4][1] = col+1;
	array[5][0] = row+1;
	array[5][1] = col;
	array[6][0] = row+1;
	array[6][1] = col-1;
	array[7][0] = row;
	array[7][1] = col-1;

	for(int i=0; i<8; i++){
		int r = array[i][0], c = array[i][1];
		if(r>=0 && r<m && c>=0 && c<n){
			string dost = classroom[r][c];
			if(DEBUG){
				cout << "check friendship of " << dost << " with " << roll << endl;
			}
			if(dost.compare("iit0000000") != 0){

				if(friends[roll].find(dost) == friends[roll].end()){
					if(DEBUG){
						cout << "enemy " << dost <<" at " <<r <<"," <<c <<"\n";
					}
					return false;
				}
			}
		}
	}
	if(DEBUG){
		cout << "can sit properly\n";
	}
	return true;
}

bool backtrack2(){
	if(seated == m*n){
		return true;
	}
	if(DEBUG){
//		cout << "backtrack called for with seated count " << seated << endl;
	}
	int min_count = INT_MAX;
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(classroom[i][j].compare("iit0000000") == 0){
				int count = 0;
				vector<string>::iterator itr = roll_numbers.begin();
				for(; itr != roll_numbers.end(); itr++){
					if(can_sit2(*itr, i, j)){
						count++;
					}
				}
				fill_count[i][j] = count;
				if(count < min_count ){
					min_count = count;
				}
			}
			else{
				fill_count[i][j] = -1;
			}
		}
	}
	int min = INT_MIN, mrow = -1, mcol = -1;
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(fill_count[i][j] == min_count){
				int array[8][2];

				array[0][0] = i-1;
				array[0][1] = j-1;
				array[1][0] = i-1;
				array[1][1] = j;
				array[2][0] = i-1;
				array[2][1] = j+1;
				array[3][0] = i;
				array[3][1] = j+1;
				array[4][0] = i+1;
				array[4][1] = j+1;
				array[5][0] = i+1;
				array[5][1] = j;
				array[6][0] = i+1;
				array[6][1] = j-1;
				array[7][0] = i;
				array[7][1] = j-1;

				int count = 0;
				for(int x=0; x<8; x++){
					int r = array[x][0], c = array[x][1];
					if(r>=0 && r<m && c>=0 && c<n){
						if(classroom[r][c].compare("iit0000000") == 0){
							count++;
						}
					}
				}
				if(count > min){
					min = count;
					mrow = i;
					mcol = j;
				}
			}
		}
	}

    vector<pair<int, int> > myvector;
    vector<string>::iterator ITR = roll_numbers.begin();
	for(; ITR != roll_numbers.end(); ITR++){
        string roll = *ITR;
		if(can_sit2(roll, mrow, mcol)){
            classroom[mrow][mcol] = roll;
			is_sitting[roll] = true;
            int just_another_var = 0;
            for(int p = 0; p < m; p++){
                for(int q = 0; q < n; q++){
                    if(classroom[p][q].compare("iit0000000") == 0){
                        vector<string>::iterator abc = roll_numbers.begin();
                        int tie_break = 0;
                        for(; abc != roll_numbers.end(); abc++){
                            if(can_sit2(*abc, p, q)){
                                tie_break++;
                            }
                        }
                        just_another_var += tie_break;
                    }
                }
            }
            myvector.push_back(make_pair(just_another_var, ITR - roll_numbers.begin()));
            classroom[mrow][mcol] = "iit0000000";
			is_sitting[roll] = false;
        }
    }

    while(!myvector.empty()){
        stable_sort(myvector.begin(), myvector.end(), CompareNode());



        string roll = roll_numbers[(*(myvector.begin())).second];
        classroom[mrow][mcol] = roll;
        is_sitting[roll] = true;
        seated++;
        if (backtrack2()){
			return true;
		}
        classroom[mrow][mcol] = "iit0000000" ;
        is_sitting[roll] = false;
        seated--;
        myvector.erase(myvector.begin());
    }

    /*
	vector<string>::iterator itr = roll_numbers.begin();
	for(; itr != roll_numbers.end(); itr++){
		string roll = *itr;
		if(can_sit2(roll, mrow, mcol)){
			if(DEBUG){
	//			cout << "accessing classroom memory\n";
			}
			classroom[mrow][mcol] = roll;
			is_sitting[roll] = true;
			seated++;
			if(DEBUG){
	//			cout << "classroom memory accessed\n";
			}
			if (backtrack2()){
				return true;
			}
			else{
				classroom[mrow][mcol] = "iit0000000" ;
				is_sitting[roll] = false;
				seated--;
			}
		}
	}
	*/
	return false;
}

void print_arrangement(){
	if(DEBUG){
	//	cout << "The classroom looks like this" << endl;
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout << classroom[i][j] << " ";
		}
		cout << endl;
	}
}

void seating_planner(){
//	cout << "Starting seating planner" << endl;
	vector<string> myRow(n, "iit0000000");
	for(int i = 0; i < m; i++){
		classroom.push_back(myRow);
	}

	vector<int> tempRow(n, -1);
	for(int i = 0; i < m; i++){
		fill_count.push_back(tempRow);
	}
	if(DEBUG){
		print_arrangement();
	}
	for(int i = 0; i < m*n; i++){
		is_sitting[roll_numbers[i]] = false;
	}

	if( backtrack2() ){
		print_arrangement();
	}
	else{
		cout << "not possible" << endl;
	}
}


int main()
{
	if(DEBUG){
	//	cout << "Starting Execution..." << endl;
	}
	int t;
	cin >> t;
	while(t--){
		test_case++;
		cin >> m >> n;
		if(DEBUG){
	//		cout << "m = " << m << ", n = " << n << endl;
		}
		int students = m*n;
		while(students--){
			string roll;
			cin >> roll;
			roll_numbers.push_back(roll);
			int friend_count;
			cin >> friend_count;
			while(friend_count--){
				string dost;
				cin >> dost;
				friends[roll].insert(dost);
			}
		}

		if(DEBUG){
	//		check_input();
		}

		seating_planner();
		clear_global_vars();
	}

	return 0;
}

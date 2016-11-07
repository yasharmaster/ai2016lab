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

bool can_sit(string &roll, int pos){
	if(DEBUG){
		cout << "trying " << roll << " on position " << pos << endl;		
	}
	int row = pos/n, col = pos%n;
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
	int mrow = -1, mcol = -1, min = INT_MAX;
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
				if(count < min ){
					min = count;
					mrow = i;
					mcol = j;
				}
			}
		}
	}
	if(mrow == -1 && mcol == -1){
		return false;
	}
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
	return false;
}

bool backtrack(int pos){
	if(pos == m*n){
		return true;
	}
	int row = pos/n, col = pos%n;
	if(DEBUG){
//		cout << "backtrack called for row=" << row << ", col=" << col << endl;		
	}
	vector<string>::iterator itr = roll_numbers.begin();
	for(; itr != roll_numbers.end(); itr++){
		string roll = *itr;
		if(can_sit(roll, pos)){
			if(DEBUG){
	//			cout << "accessing classroom memory\n";
			}
			classroom[row][col] = roll;
			is_sitting[roll] = true;
			if(DEBUG){
	//			cout << "classroom memory accessed\n";
			}
			if (backtrack(pos+1)){
				return true;
			}
			else{
				classroom[row][col] = "iit0000000" ;
				is_sitting[roll] = false;
			}
		}
	}
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

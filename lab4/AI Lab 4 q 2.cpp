#include <bits/stdc++.h>
#define DEBUG false

using namespace std;

// Custom DataTypes

typedef vector< vector<int> > GridConfig;

// Global vars

int n;
GridConfig source, dest;
// maps for storing parent configs
map<GridConfig, GridConfig> parent1;
map<GridConfig, GridConfig> parent2;


// Function Prototypes

void print_path1(GridConfig &current);
void print_config(GridConfig &A);
void shift_rows(GridConfig &current, int row, int times);
void shift_columns(GridConfig &current, int col, int times);
void copy_board(GridConfig &s, GridConfig &d);
void clear_vector(GridConfig &current);
void bds();


// Function definitions

void print_path1(GridConfig &current){
	if( DEBUG ){
		cout << "Child of first found in second" << endl;
	}
	
	stack<GridConfig> mystack;
	
	GridConfig temp = current;
	
	while( !parent1[temp].empty() ){
		mystack.push(temp);
		temp = parent1[temp];
	}
	print_config(temp);
	
	if(DEBUG){
		cout << "Half printing completed" << endl;
	}
	
	while( !mystack.empty() ){
		temp = mystack.top();
		print_config(temp);
		mystack.pop();
	}
	
	temp = parent2[current];
	while(!parent2[temp].empty()){
		print_config(temp);
		temp = parent2[temp];
	}
	print_config(temp);
}

void print_config(GridConfig &A){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << A[i][j] << " ";
		}
	}
	cout << endl;
}


void shift_rows(GridConfig &current, int row, int times){
	int curr, temp;
	
	while(times--){
		curr = current[row][0];
		for(int i=0; i<n; i++){
			temp = current[row][(i+1)%n];
			current[row][(i+1)%n] = curr;
			curr = temp;
		}
	}
}

void shift_columns(GridConfig &current, int col, int times){
	int curr, temp;
	
	while(times--){
		curr = current[0][col];
		for(int i=0; i<n; i++){
			temp = current[(i+1)%n][col];
			current[(i+1)%n][col] = curr;
			curr = temp;
		}
	}
}

void copy_board(GridConfig &s, GridConfig &d){
	vector<int> myvector;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			myvector.push_back(s[i][j]);
		}
		d.push_back(myvector);
		myvector.clear();
	}
}

void clear_vector(GridConfig &current){
	
	for(int i=0; i<n; i++){
		current[i].clear();
	}
	current.clear();
}

void bds(){
	
	if(DEBUG){
		cout << "Bidirectional Search called" << endl;
	}
	
	// queues for bfs
	queue<GridConfig> q1;
	queue<GridConfig> q2;
	queue<GridConfig> q_temp;
	
	if(DEBUG){
		cout << "Queues declared" << endl;
	}
	
	// push initial nodes to the queues
	q1.push(source);
	q2.push(dest);
	
	GridConfig empty;
	parent1[source] = empty;
	parent2[dest] = empty;
	
	if(DEBUG){
		cout << "Source & Destination pushed to the queues" << endl;
	}
	
	// stores current node's config
	GridConfig current, temp;
	
	int level = 0;
	while(true){
		
		level++;
		
		if( DEBUG ){
			cout << "Expanding source tree for depth " << level << endl;
		}
		
		while( !q1.empty() ){
			current = q1.front();
			q1.pop();
			if( parent2.find(current) != parent2.end() ){
				print_path1(current);
				return;
			}
			
			// shifting rows
			for(int i=0; i<n; i++){
				for(int j=1; j<=n-1; j++){
					copy_board(current, temp);
					shift_rows(temp, i, j);
					
					if(  parent1.find(temp) != parent1.end() ){
						clear_vector(temp);
						continue;
					}
					parent1[temp] = current;
					
					if( parent2.find(temp) != parent2.end() ){
						print_path1(temp);
						return;
					}
					q_temp.push(temp);
					
					clear_vector(temp);
				}
			}
			
			// shifting columns
			for(int i=0; i<n; i++){
				for(int j=1; j<=n-1; j++){
					copy_board(current, temp);
					shift_columns(temp, i, j);
					
					if(  parent1.find(temp) != parent1.end() ){
						clear_vector(temp);
						continue;
					}
					parent1[temp] = current;
					
					if( parent2.find(temp) != parent2.end() ){
						print_path1(temp);
						return;
					}
					q_temp.push(temp);
					
					clear_vector(temp);
				}
			}
			clear_vector(current);
		}

		while( !q_temp.empty() ){
			current = q_temp.front();
			q1.push(current);
			q_temp.pop();
			clear_vector(current);
		}
		
		if( DEBUG ){
			cout << "Expanding destination tree for depth " << level << endl;
		}
		
		while( !q2.empty() ){
			current = q2.front();
			q2.pop();
			if( parent1.find(current) != parent1.end() ){
				print_path1(current);
				return;
			}
			
			// shifting rows
			for(int i=0; i<n; i++){
				for(int j=1; j<=n-1; j++){
					copy_board(current, temp);
					shift_rows(temp, i, j);
					
					if(  parent2.find(temp) != parent2.end() ){
						clear_vector(temp);
						continue;
					}
					parent2[temp] = current;
					
					if( parent1.find(temp) != parent1.end() ){
						print_path1(temp);
						return;
					}
					q_temp.push(temp);
					
					clear_vector(temp);
				}
			}
			
			// shifting columns
			for(int i=0; i<n; i++){
				for(int j=1; j<=n-1; j++){
					copy_board(current, temp);
					shift_columns(temp, i, j);
					
					if(  parent2.find(temp) != parent2.end() ){
						clear_vector(temp);
						continue;
					}
					parent2[temp] = current;
					
					if( parent1.find(temp) != parent1.end() ){
						print_path1(temp);
						return;
					}
					q_temp.push(temp);
															
					clear_vector(temp);
				}
			}
			clear_vector(current);
		}

		while( !q_temp.empty() ){
			current = q_temp.front();
			q2.push(current);
			q_temp.pop();
			clear_vector(current);
		}

	}
	
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		
		vector<int> myvector;
		int temp;
		
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> temp;
				myvector.push_back(temp);
			}
			source.push_back(myvector);
			myvector.clear();
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> temp;
				myvector.push_back(temp);
			}
			dest.push_back(myvector);
			myvector.clear();
		}
		
		if( DEBUG ){
			cout << "\nSource :" << endl;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cout << source[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			cout << "Dest :" << endl;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cout << dest[i][j] << " "; 
				}
				cout << endl;
			}
		}
		
		// call bidirectional search function
		bds();
		
		// clearing memory for next iteration
		clear_vector(source);
		clear_vector(dest);
		parent1.clear();
		parent2.clear();
	}
	return 0;
}

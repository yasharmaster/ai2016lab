#include <bits/stdc++.h>
#define DEBUG false
using namespace std;

int **grid, m, n, sx, sy;

class Node{
public:
	int x, y;
	Node *parent;
	Node(int a, int b){
		x = a;
		y = b;
		parent = NULL;
	}
};

void print_array(int *array, int n){
	for(int i=0; i<n; i++){
		cout << array[i] << " ";
	}
}

double square(int x){
	return double(x*x);
}

void print_path(Node *current){
	if( DEBUG ){
		cout << "Print Path called for limit " << endl;
	}
	
	stack<Node *> mystack;
	Node *temp = current;
	while(temp != NULL){
		mystack.push(temp);
		temp = temp->parent;
	}
	
	while(!mystack.empty()){
		Node *temp = mystack.top();
		cout << temp->x << " " << temp->y << " ";
		mystack.pop();
	}
	cout << endl;	
}

bool dls(Node *current, double max_level, double current_level){
	int ux = current->x, uy = current->y;
	if( DEBUG ){
		cout << "DLS called with max level " << max_level << ", current level " << current_level << " and " << ux << ", " << uy << endl;
	}
	if(current_level > max_level){
		return false;
	}
	if(grid[ux][uy] == 1 && current_level <= max_level){
		print_path(current);
		return true;
	}
	if(current_level < max_level){
		int array[8][2];
    	
 		array[0][0] = ux; 	
		array[0][1] = uy+1;
		array[1][0] = ux+1;
		array[1][1] = uy+1;
		array[2][0] = ux+1;
		array[2][1] = uy;
		array[3][0] = ux+1;
		array[3][1] = uy-1;
		array[4][0] = ux;
		array[4][1] = uy-1;
		array[5][0] = ux-1;
		array[5][1] = uy-1;
		array[6][0] = ux-1;
		array[6][1] = uy;
		array[7][0] = ux-1;
		array[7][1] = uy+1;
		
		int vx, vy;
		
		for(int i=0; i<8; i++){
			vx = array[i][0];
			vy = array[i][1];
			if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
				if ( grid[vx][vy] != -1 ){
					Node *child = new Node(vx, vy);
					child->parent = current;
					bool found = dls(child, max_level, current_level + pow((square(ux-vx) + square(uy-vy)), 0.5));
					if(found){
						return found;
					}
					delete child;
				}
			}
		}
	}
	return false;
}

void iddfs(){
	if( DEBUG ){
		cout << "IDDFS called" << endl;
	}
	bool found = false;
	Node *source = new Node(sx, sy);
	
	for(int limit = 0; limit <= INT_MAX; limit++){
		found = dls(source, limit, 0);
		if(found){
			return;
		}
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> m >> n;
		grid = new int*[m];
		for(int i=0; i<m; i++){
			grid[i] = new int[n];
		}
		for(int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				cin >> grid[i][j];
			}
		}
		cin >> sx >> sy;
		if( DEBUG ){
			cout << "Grid is :" << endl;
			for(int i=0; i<m; i++){
				for(int j=0; j<n; j++){
					cout << grid[i][j] << " ";
				}
				cout << endl;
			}
			cout << "Source is : (" << sx << ", " << sy << ")\n";
		}
		iddfs();
	}
	return 0;
}

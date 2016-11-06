#include <bits/stdc++.h>
#define DEBUG false
using namespace std;

class Node {
public:
	int n;
	int **board;
	Node *parent;
	Node(int N){
		n = N;
		parent = NULL;
		board = new int*[n];
		for(int i=0; i<n; i++){
			board[i] = new int[n];
		}
	}
};

bool is_matching(Node *first, Node *second){
	int n = first->n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if( first->board[i][j] != second->board[i][j] ){
				return false;
			}
		}
	}
	return true;
}

void copy_board(Node *source, Node *dest){
	int n = source->n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			dest->board[i][j] = source->board[i][j];
		}
	}
}

void shift_rows(Node *node, int row, int times){
	int curr, temp, n = node->n;
	
	while(times--){
		curr = node->board[row][0];
		for(int i=0; i<n; i++){
			temp = node->board[row][(i+1)%n];
			node->board[row][(i+1)%n] = curr;
			curr = temp;
		}
	}
}

void shift_columns(Node *node, int col, int times){
	int curr, temp, n = node->n;
	
	while(times--){
		curr = node->board[0][col];
		for(int i=0; i<n; i++){
			temp = node->board[(i+1)%n][col];
			node->board[(i+1)%n][col] = curr;
			curr = temp;
		}
	}
}

void print_array(int *array, int n){
	for(int i=0; i<n; i++){
		cout << array[i] << " ";
	}
}

void print_path(Node *current){
	stack<int*> mystack;
	int n = current->n;
	int count = 0;
	int *array;
	
	while(current != NULL){
		count = 0;
		array = new int[n*n];
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				array[count++] = current->board[i][j];
			}
		}
		mystack.push(array);
		Node *temp = current;
		current = current->parent;
		delete temp;
	}
	
	while( !mystack.empty() ){
		array = mystack.top();
		mystack.pop();
		print_array(array, n*n);
		cout << endl;
	}
	
}

bool dls(Node *current, Node *dest, int limit){
	if( DEBUG ){
		cout << "DLS called for limit " << limit << endl;
	}
	if(limit < 0){
		return false;
	}
	if( limit==0 && is_matching(current, dest) ){
		print_path(current);
		return true;
	}
	else if (limit > 0){
		bool found = false;
	//	set_visited(current);
		int n = current->n;
		Node *temp;
		
		// shifting rows
		for(int i=0; i<n; i++){
			for(int j=1; j<=n-1; j++){
				temp = new Node(n);
				copy_board(current, temp);
				shift_rows(temp, i, j);
				temp->parent = current;
				found = dls(temp, dest, limit-1);
				if(found){
					return found;
				}
				else{
					delete temp;
				}
			}
		}
		
		// shifting columns
		for(int i=0; i<n; i++){
			for(int j=1; j<=n-1; j++){
				temp = new Node(n);
				copy_board(current, temp);
				shift_columns(temp, i, j);
				temp->parent = current;
				found = dls(temp, dest, limit-1);
				if(found){
					return found;
				}
				else{
					delete temp;
				}
			}
		}
//		return false;	
	}
	return false;
}

void iddfs(Node *source, Node *dest){
	if( DEBUG ){
		cout << "IDDFS called" << endl;
	}
	bool found = false;
	
	for(int limit = 0; limit <= INT_MAX; limit++){
		found = dls(source, dest, limit);
		if(found){
			return;
		}
	}
}

int main(){
	int t;
	cin >> t;
	Node *source, *dest;
	while(t--){
		int n;
		cin >> n;
		source = new Node(n);
		dest = new Node(n);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> source->board[i][j];
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> dest->board[i][j];
			}
		}
		if( DEBUG ){
			cout << "Source :" << endl;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cout << source->board[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			cout << "Dest :" << endl;
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					cout << dest->board[i][j] << " "; 
				}
				cout << endl;
			}
		}
		iddfs(source, dest);
	}
	return 0;
}

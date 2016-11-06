#include <bits/stdc++.h>
using namespace std;

set< vector<int> > myset;

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

void set_visited(Node *node){
	vector<int> temp;
	int n = node->n;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			temp.push_back(node->board[i][j]);
		}
	}
	
	myset.insert(temp);
}

bool is_visited(Node *node){
	vector<int> temp;
	int n = node->n;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			temp.push_back(node->board[i][j]);
		}
	}
	
	bool ret = myset.find(temp) != myset.end();
	temp.clear();
	
	return ret;
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

void bfs(Node *source, Node *dest){
	bool found = false;
	int n = source->n;
	queue<Node *> myqueue;
	myqueue.push(source);
	Node *current;
	while( !myqueue.empty() ){
		current = myqueue.front();
		if ( is_matching(current, dest) ){
			// print the path from source to destination
			found = true;
			print_path(current);
			break;
		}
		myqueue.pop();
		if ( !is_visited(current) ){
			Node *temp;
			
			// shifting rows
			for(int i=0; i<n; i++){
				for(int j=1; j<=n-1; j++){
					temp = new Node(n);
					copy_board(current, temp);
					shift_rows(temp, i, j);
					if( !is_visited(temp) ){
						temp->parent = current;
						myqueue.push(temp);
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
					if( !is_visited(temp) ){
						temp->parent = current;
						myqueue.push(temp);
					}
					else{
						delete temp;
					}
				}
			}
			
		}
		set_visited(current);
	}
	myset.erase(myset.begin(), myset.end());
	if (!found){
		cout << "not found\n";
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
/*		cout << endl;
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
*/
		bfs(source, dest);
	}
	return 0;
}

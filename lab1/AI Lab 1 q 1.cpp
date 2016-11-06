#include <iostream>
#include <stack>

using namespace std;

void BFS(int **A, int n, int source, int dest){
	
	//Testing start
/*	cout << "Graph is \n";
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "n is " << n << endl;
	cout << "source & dest are " << source << ", " << dest << endl;
*/
	//Testing end
	
	int level[n], parent[n];
	bool visited[n];
	for(int i=0; i<n; i++){
		parent[i] = -1;
		level[i] = 0;
		visited[i] = false;
	}
	
	stack<int> mystack;
	mystack.push(source);
	
	
	while(!mystack.empty()){
		int u = mystack.top();
		mystack.pop();
		visited[u] = true;
		for(int i=0; i<n; i++){
			if(A[u][i] == 1 && !visited[i]){
				parent[i] = u;
				level[i] = level[u]+1;
				mystack.push(i);
			}
		}
	}
	cout << level[dest] << endl;
	
	stack<int> util;
	int temp = dest;
	while(temp != -1){
		util.push(temp);
		temp = parent[temp];
	}
	while(!util.empty()){
		cout << util.top() << " ";
		util.pop();
	}
}

int main() {
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int **A = new int*[n];
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				A[i] = new int[n];
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				cin >> A[i][j];
			}
		}
		int source, dest;
		cin >> source >> dest;
		BFS(A, n, source, dest);
		cout << endl;
	}
	return 0;
}

#include <iostream>
#include <stack>
#include <climits>

using namespace std;

int find_min(int distance[], bool visited[], int n){
	int min = INT_MAX, index;
	for(int i = 0; i<n; i++){
		if (distance[i] < min && !visited[i]){
			index = i;
			min = distance[i];
		}
	}
	return index;
}

void Dijkstra(int **A, int n, int source, int dest){
	
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
	
	int distance[n], parent[n];
	bool visited[n];
	
	for(int i=0; i<n; i++){
		parent[i] = -1;
		distance[i] = INT_MAX;
		visited[i] = false;
	}
	
	distance[source] = 0;
	
	
	for(int i=0; i<n-1; i++){
		int u = find_min(distance, visited, n);
		visited[u] = true;
		for(int v=0; v<n; v++){
			if (!visited[v]){
				if(distance[v] > distance[u] + A[u][v] && A[u][v] != 0){
					distance[v] = distance[u] + A[u][v];
					parent[v] = u;
				}
			}
		}
	}
	
	cout << distance[dest] << endl;
	
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
		Dijkstra(A, n, source, dest);
		cout << endl;
	}
	return 0;
}

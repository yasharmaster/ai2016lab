#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX
#define ROOT pow(2, 0.5)

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<double, NODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
void dijkstra();

// Declare Global Variables
int **grid, m, n, sx, sy;
double small = 0;

class Compare{
	public:
	bool operator()(iNODE x, iNODE y ){
		return x.first > y.first;
	}
};
int square(int x){
	return x*x;
}

// Uses Dijkstra's alg. to find shortest path from source to goal 
void dijkstra(){
	// Declare a Min Heap priority Queue
	priority_queue< iNODE, vector <iNODE>, Compare > pq;
	
	// maps each node to its parent node
	map<NODE, NODE> parent;
	// maps each node to its distance from the source
	map<NODE, double> dist;
	
	// Initialize all distances to be infinite
	for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            dist[make_pair(i, j)] = INF;
        }
    }
    
    // Set distance of source to zero and push it to the priority queue
    dist[make_pair(sx, sy)] = 0;
    pq.push(make_pair(0, make_pair(sx, sy)));
    
    // Loop till priority queue is not empty
    while( !pq.empty() ){
    	NODE u = pq.top().second;
    	pq.pop();
    	int ux = u.first, uy = u.second, vx, vy;
    	double dist_u = dist[u];
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
		
		for(int i=0; i<8; i++){
			vx = array[i][0];
			vy = array[i][1];
			if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
				if ( grid[vx][vy] != -1 ){
					NODE v = make_pair(vx, vy);
					double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
					if( dist[v] > dist_u + path_cost + small ){
						dist[v] = dist_u + path_cost;
						parent[v] = u;
						pq.push(make_pair(dist[v] + small, v ));
						small += 0.0000000001;
					}
				}
			}
		}
    }	// End while loop
    
	// Find goal point
	NODE goal;
	for(int i=0; i<m; i++){
		bool found = false;
		for(int j=0; j<n; j++){
			if( grid[i][j] == 1){
				goal = make_pair(i, j);
				found = true;
			}
			if( found ){
				break;
			}
		}
	}
	
	// If goal can't be reached, print -1 and return
	if(dist[goal] == INF){
		cout << "-1\n";
		return;
	}
	
	stack<pair<int, int> > mystack;
	
	while( parent.find(goal) != parent.end() ){
		mystack.push(goal);
		goal = parent[goal];
	}
    cout << goal.first << " " << goal.second << " ";
    while( !mystack.empty() ){
    	NODE t = mystack.top();
    	mystack.pop();
    	cout << t.first << " " << t.second << " ";
    }
    cout << endl;	
    
    parent.clear();
    dist.clear();
}

// Prints the grid onto the console
void print_grid(){
    cout << "\nGrid is as follows - \n";
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    } 
}

// Prints the source coordinates
void print_source(){
	cout << "\nSource is as follows - \n";
    cout << "x = " << sx << ", y = " << sy << endl;
}

// Driver function
int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> m >> n;
        // Allocate memory to grid in the heap
        grid = new int*[m];
        for(int i=0; i<m; i++){
            grid[i] = new int[n];
        }
        // Fill grid with user input
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cin >> grid[i][j];
            }
        }
        cin >> sx >> sy;
        dijkstra();
      //  print_grid();
      //  print_source(); 
        for(int i=0; i<m; i++){
            delete grid[i];
        }
        delete grid;
    }
    return 0;
}

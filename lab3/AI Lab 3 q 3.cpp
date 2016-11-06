#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<double, NODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
void dijkstra();
int square(int x);
double path_cost(int ux, int uy, int vx, int vy);

// Declare Global Variables
int **grid, m, n, sx, sy;
double small = 0, root_two = pow(2, 0.5), root_five = pow(5, 0.5);

// Comparator transforming max heap priority queue to a min heap one
class Compare{
	public:
	bool operator()(iNODE x, iNODE y ){
		return x.first > y.first;
	}
};

// squares an integer
int square(int x){
	return x*x;
}

// returns -1 when path is invalid, path cost otherwise
double path_cost(int ux, int uy, int vx, int vy){
//	cout << "path cost called with data " << ux << ", " << uy << " and " << vx << ", " << vy << "\n";
	if( abs(ux-vx)==2 || abs(uy-vy)==2 ){
		if(abs(ux-vx)==2){
			int diff = (ux-vx)/2;
			if( grid[ux][vy] == -1 ){
				return -1;
			}
			if( grid[ux-diff][uy] == -1 ){
				return -1;
			}
			if( grid[ux-diff][vy] == -1 ){
				return -1;
			}
			if( grid[vx][uy] == -1 ){
				return -1;
			}
			if( grid[vx][vy] == -1 ){
				return -1;
			}
// 			cout << "returning root 5 \n";
			return root_five;
		}
		else{
			int diff = (uy-vy)/2;
			if( grid[vx][uy] == -1 ){
				return -1;
			}
			if( grid[ux][uy-diff] == -1 ){
				return -1;
			}
			if( grid[vx][uy-diff] == -1 ){
				return -1;
			}
			if( grid[ux][vy] == -1 ){
				return -1;
			}
			if( grid[vx][vy] == -1 ){
				return -1;
			}
//			cout << "returning root 5 \n";
			return root_five;
		}
	}
	else if(vx == ux || vy == uy){
		if(grid[vx][vy] == -1){
			return -1;
		}
		return 1;
	}
	else{
		if( grid[ux][vy] == -1 ){
			return -1;
		}
		if( grid[vx][uy] == -1 ){
			return -1;
		}
		if( grid[vx][vy] == -1 ){
			return -1;
		}
		return root_two;
	}
}

// Uses Dijkstra's alg. to find shortest path from source to goal 
void dijkstra(){
	
//	cout << "dijkstra called\n";
	
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
    	
  //  	cout << ux << ", " << uy << " popped\n";
    	
    	if(grid[ux][uy] == 1){
  //  		cout << "gem found, exiting...\n";
    		break;
    	}
    	double dist_u = dist[u];
    	int array[16][2];
    	
 		array[0][0] = ux; 	
		array[0][1] = uy+1;	// East
 		array[1][0] = ux+1; 	
		array[1][1] = uy+2;
 		array[2][0] = ux+1; 
		array[2][1] = uy+1; // South East
 		array[3][0] = ux+2; 	
		array[3][1] = uy+1; 
 		array[4][0] = ux+1; 
		array[4][1] = uy; // South
 		array[5][0] = ux+2; 	
		array[5][1] = uy-1;
 		array[6][0] = ux+1; 	
		array[6][1] = uy-1; // South West
 		array[7][0] = ux+1; 	
		array[7][1] = uy-2;
 		array[8][0] = ux; 
		array[8][1] = uy-1;	// West
 		array[9][0] = ux-1; 	
		array[9][1] = uy-2;
 		array[10][0] = ux-1; 	
		array[10][1] = uy-1;	// North West
 		array[11][0] = ux-2; 	
		array[11][1] = uy-1;
 		array[12][0] = ux-1; 	
		array[12][1] = uy;	// North
 		array[13][0] = ux-2; 	
		array[13][1] = uy+1;
 		array[14][0] = ux-1; 	
		array[14][1] = uy+1;	// North East
 		array[15][0] = ux-1; 	
		array[15][1] = uy+2;
		
//		cout << "Array all set \n";
		
		// Loop for all possible moves
		for(int i=0; i<16; i++){
			vx = array[i][0];
			vy = array[i][1];
//			cout << "checking for child " << vx << ", " << vy << endl;
			if( !(vx < m && vx >= 0 && vy < n && vy >= 0) ){
//				cout << "rejected first\n";
				continue;	// invalid path
			}
			double cost = path_cost(ux, uy, vx, vy);
//			cout << "path cost is " << cost << endl;
			if(cost == -1){
//				cout << "rejected second\n";
				continue;	// invalid path
			}
			NODE v = make_pair(vx, vy);
			if( dist[v] > dist_u + cost + small ){
				dist[v] = dist_u + cost;
				parent[v] = u;
				pq.push(make_pair(dist[v] + small, v ));
	//			cout << "pushed to queue\n";
				small += 0.0000000001;
			}
			else{
//				cout << "not pushed to the queue\n";
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

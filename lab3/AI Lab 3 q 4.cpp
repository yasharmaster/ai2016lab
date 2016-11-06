#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX
#define ROOT pow(2, 0.5)

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<NODE, int> dNODE;
typedef pair<double, dNODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
void dijkstra();
double find_action_cost(int ud, int vd);

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
	map<dNODE, dNODE> parent;
	// maps each node to its distance from the source
	map<dNODE, double> dist;
	
	// Initialize all distances to be infinite
	for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
        	for(int k=1; k<=8; k++){
        		dist[make_pair(make_pair(i, j), k)] = INF;
        	}
        }
    }
    
    // Set distance of source to zero and push it to the priority queue
    dist[make_pair(make_pair(sx, sy), 1)] = 0;
    pq.push(make_pair(0, make_pair(make_pair(sx, sy), 1)));
    
    int min_direction = -1;
    
    // Loop till priority queue is not empty
    while( !pq.empty() ){
    	dNODE dnode = pq.top().second;
    	NODE u = dnode.first;
    	pq.pop();
    	int ux = u.first, uy = u.second, ud = dnode.second, vx, vy, vd;
    	
    	if( grid[ux][uy] == 1){
    		min_direction = ud;
			break;
    	}
		    	
    	double dist_u = dist[dnode];
    
		int array[8][3];
    	
 		array[0][0] = ux; 	
		array[0][1] = uy+1;
		array[0][2] = 1;
		array[1][0] = ux+1;
		array[1][1] = uy+1;
		array[1][2] = 2;
		array[2][0] = ux+1;
		array[2][1] = uy;
		array[2][2] = 3;
		array[3][0] = ux+1;
		array[3][1] = uy-1;
		array[3][2] = 4;
		array[4][0] = ux;
		array[4][1] = uy-1;
		array[4][2] = 5;
		array[5][0] = ux-1;
		array[5][1] = uy-1;
		array[5][2] = 6;
		array[6][0] = ux-1;
		array[6][1] = uy;
		array[6][2] = 7;
		array[7][0] = ux-1;
		array[7][1] = uy+1;
		array[7][2] = 8;
		
		for(int i=0; i<8; i++){
			vx = array[i][0];
			vy = array[i][1];
			vd = array[i][2];
			if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
				if ( grid[vx][vy] != -1 ){
					
					dNODE child = make_pair(make_pair(vx, vy), vd);
					
					double action_cost = 5*(abs(ud-vd) <= 4 ? abs(ud-vd) : 8 - abs(ud-vd));
					
					double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5) + action_cost;
					
					if( dist[child] > dist_u + path_cost + small ){
						dist[child] = dist_u + path_cost;
						parent[child] = dnode;
						pq.push(make_pair(dist[child] + small, child ));
						small += 0.0000000001;
					}
				}
			}
		}
    }	// End while loop
    
    
	if( min_direction == -1){
		cout << "-1\n";
		return;
	}
    
	// Find goal point
	int gx, gy;
	for(gx=0; gx<m; gx++){
		bool found = false;
		for(gy=0; gy<n; gy++){
			if( grid[gx][gy] == 1){
				found = true;
				break;
			}
		}
		if( found ){
			break;
		}
	}
	
	NODE g = make_pair(gx, gy);
	
	dNODE goal = make_pair(g, min_direction);
	
	stack<dNODE > mystack;
	
	while( parent.find(goal) != parent.end() ){
		mystack.push(goal);
		goal = parent[goal];
	}
    cout << goal.first.first << " " << goal.first.second << " ";
    while( !mystack.empty() ){
    	dNODE t = mystack.top();
    	mystack.pop();
    	cout << t.first.first << " " << t.first.second << " ";
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

#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX
#define ROOT pow(2, 0.5)

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<NODE, vector<NODE> > gNODE;
typedef pair<gNODE, int> tNODE;
typedef pair<double, tNODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
void dijkstra();

// Declare Global Variables
int **grid, m, n, sx, sy, Y;
double eta, alpha;
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
//	cout << "dijkstra called\n";
	
	// Declare a Min Heap priority Queue
	priority_queue< iNODE, vector <iNODE>, greater<iNODE> > pq;
	
	// maps each node to its parent node
	map<tNODE, tNODE> parent;
	
	// maps each node to its distance from the source
	map<tNODE, double> dist;
	
	// empty vector for storing coordinates of the gems collected so far
	vector<NODE> gems_vector;
    
	// flag
	bool found = false;
	tNODE goal;
	
	double d = 0;
	if( grid[sx][sy] > 0 ){
		d = alpha;
		gems_vector.push_back(make_pair(sx, sy));
	}
    
    // Set distance of source to zero and push it to the priority queue
    dist[make_pair(make_pair(make_pair(sx, sy), gems_vector ), 0)] = d;
    pq.push(make_pair(d, make_pair(make_pair(make_pair(sx, sy), gems_vector ), 0)));
 //   cout << "source pushd to the queue\n";
    
    // Loop till priority queue is not empty
    while( !pq.empty() ){
    	
    	tNODE popped = pq.top().second;
    	pq.pop();
    	
    	NODE u = popped.first.first;
		gems_vector = popped.first.second;
		
		int ux = u.first, uy = u.second, vx, vy, ut = popped.second;
    	double dist_popped = dist[popped];
    	
    //	cout << ux << ", " << uy << " popped\n";
    //	cout << "distance of " << ux << ", " << uy << " is " << dist_popped << endl;
    	
    	
		// Check if gems collected so far are enough
		vector<NODE>::iterator itr = gems_vector.begin();
		int temp_sum = 0;
		for( ; itr != gems_vector.end(); ++itr){
			temp_sum += grid[(*itr).first][(*itr).second];
		}
		if(temp_sum >= eta){
			found = true;
			goal = popped;
		//	cout << "gems collected\n";
			break;
		}

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
					bool is_collected = false;
					vector<NODE>::iterator it = gems_vector.begin();
					for( ; it != gems_vector.end(); ++it){
						if( (*it) == make_pair(vx, vy) ){
							is_collected = true;
							break;
						}
					}
					if( is_collected || grid[vx][vy] == 0 ){
						// gem is already collected or this place has no gem
						NODE v = make_pair(vx, vy);
						gNODE ch = make_pair(v, gems_vector);
						tNODE child = make_pair(ch, ut);
						double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
						if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
							dist[child] = dist_popped + path_cost+small;
							parent[child] = popped;
							pq.push(make_pair(dist[child] , child ));
						//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << endl;
							small += 0.00000000001;
						}
					}
					else{
						// new gem found
						NODE v = make_pair(vx, vy);
						vector<NODE> temp_gems_vector = gems_vector;
						temp_gems_vector.push_back(v);
						gNODE ch = make_pair(v, temp_gems_vector);
						tNODE child = make_pair(ch, ut);
						double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5) + alpha;
						
						if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
							dist[child] = dist_popped + path_cost+small;
							parent[child] = popped;
							pq.push(make_pair(dist[child] , child ));
//							cout << vx << ", " << vy << " pushed with gem with dist = " << dist[child] << endl;
							small += 0.00000000001;
						}
					}
				}
				if( grid[vx][vy] == -1 && ut < Y){
						NODE v = make_pair(vx, vy);
						gNODE ch = make_pair(v, gems_vector);
						tNODE child = make_pair(ch, ut+1);
						double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
						if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
							dist[child] = dist_popped + path_cost+small;
							parent[child] = popped;
							pq.push(make_pair(dist[child] , child ));
						//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << endl;
							small += 0.00000000001;
						}
				}
			}
		}
    }	// End while loop
    
    
	// If goal can't be reached, print -1 and return
	if( !found ){
		cout << "-1\n";
		return;
	}
	
//	cout << "printing result\n";
	
	stack<tNODE> mystack;
	
	while( parent.find(goal) != parent.end() ){
		mystack.push(goal);
		goal = parent[goal];
	}
    cout << goal.first.first.first << " " << goal.first.first.second << " ";
    while( !mystack.empty() ){
    	NODE t = mystack.top().first.first;
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
    cout << "eta = " << eta << ", alpha = " << alpha << endl;
}

// Driver function
int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> m >> n >> eta >> Y >> alpha;
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
    //    print_grid();
    //    print_source(); 
        for(int i=0; i<m; i++){
            delete grid[i];
        }
        delete grid;
    }
    return 0;
}

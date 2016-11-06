#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX
#define ROOT pow(2, 0.5)

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<NODE, vector<NODE> > gNODE;
typedef pair<bool, bool> POWER;
typedef pair<gNODE, POWER> sNODE;
typedef pair<double, sNODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
void dijkstra();

// Declare Global Variables
int **grid, m, n, sx, sy;
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
	map<sNODE, sNODE> parent;
	
	// maps each node to its distance from the source
	map<sNODE, double> dist;
	
	// empty vector for storing coordinates of the gems collected so far
	vector<NODE> gems_vector;
    
	// flag
	bool found = false;
	sNODE goal;
	bool source_has_power = false;
	double initial_dist = 0;
	
	if( grid[sx][sy] > 0 ){
		initial_dist = alpha;
		gems_vector.push_back(make_pair(sx, sy));
	}
	else if( grid[sx][sy] == -2 ){
		source_has_power = true;
	}
	
	sNODE source_node = make_pair( make_pair(make_pair(sx, sy), gems_vector), make_pair(source_has_power, false));
    
    // Set distance of source to zero and push it to the priority queue
    dist[source_node] = initial_dist;
    pq.push(make_pair(initial_dist, source_node ));
 //   cout << "source pushed to the queue\n";
    
    // Loop till priority queue is not empty
    while( !pq.empty() ){
    	
    	sNODE popped = pq.top().second;
    	pq.pop();
    	
    	POWER parent_power = popped.second;
    	NODE u = popped.first.first;
		gems_vector = popped.first.second;
		
		bool parent_has_power = parent_power.first, parent_used_power = parent_power.second;
		
		int ux = u.first, uy = u.second, vx, vy;
    	double dist_popped = dist[popped];
    	
    //	cout << ux << ", " << uy << " popped with distance = " << dist_popped << endl;
    //	cout << "has power = " << parent_has_power << ", used  power = " << parent_used_power << endl;
    	
		// Check if gems collected so far are enough
		vector<NODE>::iterator itr = gems_vector.begin();
		int temp_sum = 0;
		for( ; itr != gems_vector.end(); ++itr){
			temp_sum += grid[(*itr).first][(*itr).second];
		}
		if(temp_sum >= eta){
			found = true;
			goal = popped;
		//	cout << "gems collected, exiting....\n";
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
		
		
		if( !parent_has_power ){
			for(int i=0; i<8; i++){
				vx = array[i][0];
				vy = array[i][1];
				if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
					if ( grid[vx][vy] > -1 ){
						// this place has no power
						
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
							sNODE child = make_pair(ch, make_pair(false, false));
							double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
							if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
								dist[child] = dist_popped + path_cost+small;
								parent[child] = popped;
								pq.push(make_pair(dist[child] , child ));
							//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << " without power " << endl;
								small += 0.00000000001;
							}
						}
						else{
							// new gem found
							NODE v = make_pair(vx, vy);
							vector<NODE> temp_gems_vector = gems_vector;
							temp_gems_vector.push_back(v);
							gNODE ch = make_pair(v, temp_gems_vector);
							sNODE child = make_pair(ch, make_pair(false, false));
							double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5) + alpha;
							
							if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
								dist[child] = dist_popped + path_cost+small;
								parent[child] = popped;
								pq.push(make_pair(dist[child] , child ));
							//	cout << vx << ", " << vy << " pushed with gem with dist = " << dist[child] << " without power "  << endl;
								small += 0.00000000001;
							}
						}
					}
					else if ( grid[vx][vy] == -2 ){
						// this place has power
						
						NODE v = make_pair(vx, vy);
						gNODE ch = make_pair(v, gems_vector);
						sNODE child = make_pair(ch, make_pair(true, false));
						double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
						if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
							dist[child] = dist_popped + path_cost+small;
							parent[child] = popped;
							pq.push(make_pair(dist[child] , child ));
						//	cout << vx << ", " << vy << " collected power n pushed with dist = " << dist[child] << endl;
							small += 0.00000000001;
						}
					}
				}
			}
		}
		else{
			if( parent_used_power ){
				// power already used, cannot use again
				for(int i=0; i<8; i++){
					vx = array[i][0];
					vy = array[i][1];
					if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
						if ( grid[vx][vy] > -1 || grid[vx][vy] == -2 ){
							// this place has no power
							
							bool is_collected = false;
							vector<NODE>::iterator it = gems_vector.begin();
							for( ; it != gems_vector.end(); ++it){
								if( (*it) == make_pair(vx, vy) ){
									is_collected = true;
									break;
								}
							}
							if( is_collected || grid[vx][vy] == 0 || grid[vx][vy] == -2 ){
								// gem is already collected or this place has no gem
								NODE v = make_pair(vx, vy);
								gNODE ch = make_pair(v, gems_vector);
								sNODE child = make_pair(ch, make_pair(true, true));
								double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
								if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
									dist[child] = dist_popped + path_cost+small;
									parent[child] = popped;
									pq.push(make_pair(dist[child] , child ));
								//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << " without power " << endl;
									small += 0.00000000001;
								}
							}
							else{
								// new gem found
								NODE v = make_pair(vx, vy);
								vector<NODE> temp_gems_vector = gems_vector;
								temp_gems_vector.push_back(v);
								gNODE ch = make_pair(v, temp_gems_vector);
								sNODE child = make_pair(ch, make_pair(true, true));
								double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5) + alpha;
								
								if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
									dist[child] = dist_popped + path_cost+small;
									parent[child] = popped;
									pq.push(make_pair(dist[child] , child ));
								//	cout << vx << ", " << vy << " pushed with gem with dist = " << dist[child] << " without power " << endl;
									small += 0.00000000001;
								}
							}
						}
					}
				}
			}
			else{
				
				// Not using the superpower
				for(int i=0; i<8; i++){
					vx = array[i][0];
					vy = array[i][1];
					if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
						if ( grid[vx][vy] > -1 || grid[vx][vy] == -2){
							
							bool is_collected = false;
							vector<NODE>::iterator it = gems_vector.begin();
							for( ; it != gems_vector.end(); ++it){
								if( (*it) == make_pair(vx, vy) ){
									is_collected = true;
									break;
								}
							}
							if( is_collected || grid[vx][vy] == 0  || grid[vx][vy] == -2 ){
								// gem is already collected or this place has no gem
								NODE v = make_pair(vx, vy);
								gNODE ch = make_pair(v, gems_vector);
								sNODE child = make_pair(ch, make_pair(true, false));
								double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5);
								if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
									dist[child] = dist_popped + path_cost+small;
									parent[child] = popped;
									pq.push(make_pair(dist[child] , child ));
								//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << " without power " << endl;
									small += 0.00000000001;
								}
							}
							else{
								// new gem found
								NODE v = make_pair(vx, vy);
								vector<NODE> temp_gems_vector = gems_vector;
								temp_gems_vector.push_back(v);
								gNODE ch = make_pair(v, temp_gems_vector);
								sNODE child = make_pair(ch, make_pair(true, false));
								double path_cost = pow((square(ux-vx) + square(uy-vy)), 0.5) + alpha;
								
								if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
									dist[child] = dist_popped + path_cost+small;
									parent[child] = popped;
									pq.push(make_pair(dist[child] , child ));
								//	cout << vx << ", " << vy << " pushed with gem with dist = " << dist[child] << " without power " << endl;
									small += 0.00000000001;
								}
							}
						}
					}
				}
				
				// Using the superpower
				for(int vx=ux-5; vx<=ux+5 ; vx++ ){
					for(int vy=uy-5; vy <=uy+5 ; vy++){
						if( pow(ux-vx,2) + pow(uy-vy,2) <= 25){
							if( vx < m && vx >= 0 && vy < n && vy >= 0 ){
								if ( grid[vx][vy] > -1 || grid[vx][vy] == -2){									
									bool is_collected = false;
									vector<NODE>::iterator it = gems_vector.begin();
									for( ; it != gems_vector.end(); ++it){
										if( (*it) == make_pair(vx, vy) ){
											is_collected = true;
											break;
										}
									}
									if( is_collected || grid[vx][vy] == 0  || grid[vx][vy] == -2 ){
										// gem is already collected or this place has no gem
										NODE v = make_pair(vx, vy);
										gNODE ch = make_pair(v, gems_vector);
										sNODE child = make_pair(ch, make_pair(true, true));
										double path_cost = 1;
										if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
											dist[child] = dist_popped + path_cost+small;
											parent[child] = popped;
											pq.push(make_pair(dist[child] , child ));
										//	cout << vx << ", " << vy << " pushed without gem with dist = " << dist[child] << " with power " << endl;
										//	small += 0.00000000001;
										}
									}
									else{
										// new gem found
										NODE v = make_pair(vx, vy);
										vector<NODE> temp_gems_vector = gems_vector;
										temp_gems_vector.push_back(v);
										gNODE ch = make_pair(v, temp_gems_vector);
										sNODE child = make_pair(ch, make_pair(true, true));
										double path_cost =  alpha + 1;
										
										if( dist.find(child) == dist.end() || dist[child] > dist_popped + path_cost + small ){
											dist[child] = dist_popped + path_cost+small;
											parent[child] = popped;
											pq.push(make_pair(dist[child] , child ));
										//	cout << vx << ", " << vy << " pushed with gem with dist = " << dist[child] << " with power " << endl;
										//	small += 0.00000000001;
										}
									}
								}
							}
						}
					}
				}
				small += 0.00000000001;
			}
		}
		

    }	// End while loop
    
    
	// If goal can't be reached, print -1 and return
	if( !found ){
		cout << "-1\n";
		return;
	}
	
//	cout << "printing result\n";
	
	stack<sNODE> mystack;
	
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
        cin >> m >> n >> eta >> alpha;
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

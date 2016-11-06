#include <bits/stdc++.h>

// Init Macros
#define INF INT_MAX
#define ROOTTWO 1.41421356
#define DEBUG false

using namespace std;

// Define DataTypes
typedef pair<int, int> NODE;
typedef pair<double, NODE> iNODE;

// Function Prototypes
void print_grid();
void print_source();
int square(int x);
void BDS();

// Declare Global Variables
int **grid, m, n, sx, sy, gx, gy;
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

void BDS(){
	if(DEBUG){
		cout << "BDS Called\n";
	}
	// Declare Min Heap priority Queues
	priority_queue< iNODE, vector <iNODE>, Compare > pq1;
	priority_queue< iNODE, vector <iNODE>, Compare > pq2;
	
	// maps each node to its distance of the from a+b*ROOTTWO
	map<NODE, NODE> dist1;
	map<NODE, NODE> dist2;
	
	
	
	// Initialize all distances to be infinite
	for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            dist1[make_pair(i, j)] = make_pair(-1, -1);
            dist2[make_pair(i, j)] = make_pair(-1, -1);
        }
    }
    
    dist1[make_pair(sx, sy)] = make_pair(0,0);
    dist2[make_pair(gx, gy)] = make_pair(0,0);
    
    pq1.push(make_pair(0, make_pair(sx,sy)));
    pq2.push(make_pair(0, make_pair(gx,gy)));

    double min_dist = INF;
    NODE mid;
    
    while( !(pq1.empty() && pq2.empty()) ){
    	
    	if(DEBUG){
			cout << "Outer while loop\n";
		}
    	while(!pq1.empty()){
    		
    		if(DEBUG){
				cout << "Inner while loop 1\n";
			}
    		
    		NODE u = pq1.top().second;
    		pq1.pop();
    		
    		int ua = dist1[u].first;
    		int ub = dist1[u].second;
    		
    		double dist_u = ua + ub*ROOTTWO;
    		
    		if( !(dist2[u].first == -1 && dist2[u].second == -1)){
    			double current_ans = dist2[u].first + (dist2[u].second)*ROOTTWO + dist_u;
    			if( current_ans < min_dist ){
    				min_dist = current_ans;
    				mid = u;
    			}
    		}
    		
	    	int ux = u.first, uy = u.second, vx, vy;
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
						double dist_v;
						if( dist1[v].first == -1 && dist1[v].second == -1){
							if(path_cost == 1){
								dist_v = dist_u + 1;
								dist1[v] = make_pair(ua + 1, ub);
							}
							else{
								dist_v = dist_u + ROOTTWO;
								dist1[v] = make_pair(ua, ub+1);
							}
							pq1.push(make_pair(dist_v + small, v ));
							small += 0.0000000001;
						}
						else{
							int va = dist1[v].first;
							int vb = dist1[v].second;
							dist_v =  va + vb*ROOTTWO;
							
							if(dist_v > dist_u + path_cost){
								if(path_cost == 1){
									dist_v = dist_u + 1;
									dist1[v] = make_pair(ua + 1, ub);
								}
								else{
									dist_v = dist_u + ROOTTWO;
									dist1[v] = make_pair(ua, ub+1);
								}
								pq1.push(make_pair(dist_v + small, v ));
								small += 0.0000000001;
							}
						}
						
			    		if( !(dist2[v].first == -1 && dist2[v].second == -1)){
			    			double current_ans = dist2[v].first + (dist2[v].second)*ROOTTWO + dist_v;
			    			if( current_ans < min_dist ){
			    				min_dist = current_ans;
			    				mid = v;
			    			}
			    		}
					}
				}
			}
    	}
  	
    	while(!pq2.empty()){
    		
		    if(DEBUG){
				cout << "Inner while loop 2\n";
			}

    		NODE u = pq2.top().second;
    		pq2.pop();
    		
    		int ua = dist2[u].first;
    		int ub = dist2[u].second;
    		
    		double dist_u = ua + ub*ROOTTWO;
    		
    		if( !(dist1[u].first == -1 && dist1[u].second == -1)){
    			double current_ans = dist1[u].first + (dist1[u].second)*ROOTTWO + dist_u;
    			if( current_ans < min_dist ){
    				min_dist = current_ans;
    				mid = u;
    			}
    		}
    		
	    	int ux = u.first, uy = u.second, vx, vy;
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
						double dist_v;
						if( dist2[v].first == -1 && dist2[v].second == -1){
							if(path_cost == 1){
								dist_v = dist_u + 1;
								dist2[v] = make_pair(ua + 1, ub);
							}
							else{
								dist_v = dist_u + ROOTTWO;
								dist2[v] = make_pair(ua, ub+1);
							}
							pq2.push(make_pair(dist_v + small, v ));
							small += 0.0000000001;
						}
						else{
							int va = dist2[v].first;
							int vb = dist2[v].second;
							dist_v =  va + vb*ROOTTWO;
							
							if(dist_v > dist_u + path_cost){
								if(path_cost == 1){
									dist_v = dist_u + 1;
									dist2[v] = make_pair(ua + 1, ub);
								}
								else{
									dist_v = dist_u + ROOTTWO;
									dist2[v] = make_pair(ua, ub+1);
								}
								pq2.push(make_pair(dist_v + small, v ));
								small += 0.0000000001;
							}
						}
						
			    		if( !(dist1[v].first == -1 && dist1[v].second == -1)){
			    			double current_ans = dist1[v].first + (dist1[v].second)*ROOTTWO + dist_v;
			    			if( current_ans < min_dist ){
			    				min_dist = current_ans;
			    				mid = v;
			    			}
			    		}
					}
				}
			}
    	}
    }
    
    cout << dist1[mid].first + dist2[mid].first << " " << dist1[mid].second + dist2[mid].second << endl;
    
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

// Prints the dest coordinates
void print_dest(){
	cout << "\nDestination is as follows - \n";
    cout << "x = " << gx << ", y = " << gy << endl;
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
                if(grid[i][j] == 1){
                	gx = i;
                	gy = j;
                }
            }
        }
        cin >> sx >> sy;
        
        // Bidirectional Search
        BDS();
        
		if(DEBUG){
	        print_grid();
	        print_source(); 
	        print_dest();
        }

        for(int i=0; i<m; i++){
            delete grid[i];
        }
        delete grid;
    }
    return 0;
}

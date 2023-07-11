#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

vector<int> assignment;
bool flip;
using C = ll;
 
C hungarian(vector<vector<C>> costs){
	int n = int(costs.size());
	int m = costs.empty() ? 0 : int(costs[0].size());
	
	flip = false;
	if(n > m){
		vector<vector<C>> new_costs(m,vector<C>(n));
 
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				new_costs[j][i] = costs[i][j];
			}
		}
		
		swap(costs, new_costs);
		swap(n,m);
		flip = true;
	}
	
	vector<C> u(n+1), v(m+1);
	vector<int> p(m+1), way(m+1);
 
	for(int i = 1; i <= n; i++){
		vector<C> min_v(m+1, INF64);
		vector<bool> used(m+1, false);
 
		p[0] = i;
		int j0 = 0;
		do{
			used[j0] = true;
			int i0 = p[j0];
			int j1 = 0;
			C delta = INF64;
 
			for(int j = 1; j <= m; j++){
				if(!used[j]){
					C cur = costs[i0-1][j-1] - u[i0] - v[j];
 
					if(cur < min_v[j]){
						min_v[j] = cur;
						way[j] = j0;
					}
 
					if(min_v[j] < delta){
						delta = min_v[j];
						j1 = j;
					}
				}
			}
 
			for(int j = 0; j <= m; j++){
				if(used[j]){
					u[p[j]] += delta;
					v[j] -= delta;
				}
			 	else{
					min_v[j] -= delta;
				}
			}
 
			j0 = j1;
		} while(p[j0] != 0);
 
		do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
		
	}
	
	//p[j] is the row assignment of column j ( both 1-based), if flip = true
	//p[j] is the column assignment of row j (both 1-based) of the matriz costs.
	assignment = p;
 
	return -v[0];
 
}

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

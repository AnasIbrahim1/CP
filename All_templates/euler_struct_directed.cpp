#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct euler_walk_directed { 
    // doesn't handle the case of no edges, zero based
    int n, m;
    vector<int> head, nxt, to, in_deg, out_deg, tour;
    int tour_idx, num_vis;
    euler_walk_directed() {}
    
    void resize(int max_nodes, int max_edges) {
        nxt.resize(max_edges + 5), to.resize(max_edges + 5);
        tour.resize(max_edges + 5), head.resize(max_nodes + 5, -1);
        in_deg.resize(max_nodes + 5), out_deg.resize(max_nodes + 5);
    }

    void init(int num_nodes, int max_edges) { // if global and keeping between test cases
        n = num_nodes, num_vis = m = tour_idx = 0;
        fill(head.begin(), head.begin() + n + 5, -1);
        fill(in_deg.begin(), in_deg.begin() + n + 5, 0);
        fill(out_deg.begin(), out_deg.begin() + n + 5, 0);
    }

    void add_edge(int u, int v) {
        to[m] = v;
        nxt[m] = head[u];
        head[u] = m++;
        in_deg[v]++; out_deg[u]++;
    }


    bool check_eulerian_circuit() {
        for (int i = 0; i < n; i++) if (in_deg[i] != out_deg[i]) return false;
        return true;
    }

    bool check_eulerian_trail() {
        int count_non_zero = 0;
        for (int i = 0; i < n; i++) if (in_deg[i] != out_deg[i]) count_non_zero++;
        if (count_non_zero == 0) return true;
        vector<int> diff;
        for (int i = 0; i < n; i++) if (in_deg[i] != out_deg[i]) diff.push_back(in_deg[i] - out_deg[i]);
        sort(diff.begin(), diff.end());
        return (diff == vector<int>({-1, 1}));
    }

    void euler(int u) {
        for (int& e = head[u], v; ~e && (v = to[e], 1);) {
            int back_up = e;
            e = nxt[e];
            num_vis++;
            euler(v);
        }
        tour[tour_idx++] = u;
    }

    bool euler_circuit() {
        if (!check_eulerian_circuit()) return false;
        for (int i = 0; i < n; i++) if (out_deg[i]) {
            euler(i);
            break;
        }
        if (num_vis != m) return false;
        return true;
    }

    bool euler_circuit(int src) {
        if (!check_eulerian_circuit()) return false;
        if (!out_deg[src]) return false;
        euler(src);
        if (num_vis != m) return false;
        return true;
    }

    bool euler_trail() {
        if (euler_circuit()) return true;
        if (!check_eulerian_trail()) return false;
        for (int i = 0; i < n; i++) if (out_deg[i] - in_deg[i] == 1) { 
            euler(i);
            break; 
        }
        if (num_vis != m) return false;
        return true;
    }

    bool euler_trail(int src) {
        if (euler_circuit(src)) return true;
        if (!check_eulerian_trail()) return false;
        if (out_deg[src] - in_deg[src] != 1) return false;
        euler(src);
        if (num_vis != m) return false;
        reverse(tour.begin(), tour.begin() + tour_idx);
        return true;
    }

};

euler_walk_directed euler_walk;

void solve() {
    int n, m;
    cin >> n >> m;
    euler_walk.init(n, m);
    for (int t = 0; t < m; t++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        euler_walk.add_edge(u, v);
    }
    if (!euler_walk.euler_trail(0) || euler_walk.tour[euler_walk.tour_idx - 1] != n - 1) return void(cout << "IMPOSSIBLE\n");
    for (int i = 0; i < euler_walk.tour_idx; i++)
        cout << euler_walk.tour[i] + 1 << " ";
    cout << "\n";
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    euler_walk.resize(int(1e5 + 9), int(2e5 + 9));
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
} 
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct euler_walk_undirected { // doesn't handle the case of no edges, zero based
    int n, m;
    vector<int> head, nxt, to, deg, vis, tour;
    int tour_idx, num_vis;
    euler_walk_undirected() {}
    
    void resize(int max_nodes, int max_edges) {
        max_edges <<= 1;
        nxt.resize(max_edges + 5), to.resize(max_edges + 5), vis.resize(max_edges + 5);
        tour.resize(max_edges + 5), head.resize(max_nodes + 5, -1), deg.resize(max_nodes + 5);
    }

    void init(int num_nodes, int max_edges) { // if global and keeping between test cases
        n = num_nodes, num_vis = m = tour_idx = 0;
        fill(head.begin(), head.begin() + n + 5, -1);
        fill(deg.begin(), deg.begin() + n + 5, 0);
    }

    void add_dir_edge(int u, int v) {
        to[m] = v;
        nxt[m] = head[u];
        head[u] = m++;
    }

    void add_edge(int u, int v) {
        add_dir_edge(u, v), add_dir_edge(v, u);
        deg[u]++, deg[v]++;
    }

    bool check_eulerian_circuit() {
        for (int i = 0; i < n; i++) if (deg[i] & 1) return false;
        return true;
    }

    bool check_eulerian_trail() {
        int num_odd = 0;
        for (int i = 0; i < n; i++) num_odd += (deg[i] & 1);
        return (num_odd == 2 || num_odd == 0);
    }

    void euler(int u) {
        for (int& e = head[u], v; ~e && (v = to[e], 1);) {
            int back_up = e;
            e = nxt[e];
            if (vis[back_up] == tc) continue;
            vis[back_up] = vis[back_up ^ 1] = tc; num_vis += 2;
            euler(v);
        }
        tour[tour_idx++] = u;
    }

    bool euler_circuit() {
        if (!check_eulerian_circuit()) return false;
        for (int i = 0; i < n; i++) if (deg[i]) {
            euler(i);
            break;
        }
        if (num_vis != m) return false;
        return true;
    }

    bool euler_circuit(int src) {
        if (!check_eulerian_circuit()) return false;
        if (!deg[src]) return false;
        euler(src);
        if (num_vis != m) return false;
        return true;
    }

    bool euler_trail() {
        if (euler_circuit()) return true;
        if (!check_eulerian_trail()) return false;
        for (int i = 0; i < n; i++) if (deg[i] & 1) { 
            euler(i);
            break; 
        }
        if (num_vis != m) return false;
        return true;
    }

    bool euler_trail(int src) {
        if (euler_circuit(src)) return true;
        if (!check_eulerian_trail()) return false;
        if (deg[src] % 2 == 0) return false;
        euler(src);
        if (num_vis != m) return false;
        return true;
    }

};

euler_walk_undirected euler_walk;

void solve() {
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
} 
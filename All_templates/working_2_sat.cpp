#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct two_sat { // zero based
    int n, num_vars;
    vector<vector<int>> g, trans;
    vector<bool> vis, assignment;
    vector<int> order, comp;
    two_sat() {}
    two_sat(int number_of_variables) { init(number_of_variables); }

    void init(int _n) {
        num_vars = _n;
        n = 2 * num_vars;
        g.resize(n); trans.resize(n);
        vis.resize(n); assignment.resize(n);
    }

    void dfs1(int v) {
        vis[v] = true;
        for (int u : g[v]) if (!vis[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : trans[v]) if (comp[u] == -1) dfs2(u, cl);
    }

    bool solve_2SAT() {
        order.clear();
        vis.assign(n, false);
        for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);
        
        comp.assign(n, -1);
        for (int i = n - 1, j = 0; i >= 0; --i) {
            int v = order[i];
            if (comp[v] == -1) dfs2(v, j++);
        }
        
        assignment.assign(n / 2, false);
        for (int i = 0; i < n; i += 2) {
            if (comp[i] == comp[i + 1]) return false;
            assignment[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }

    void add_disjunction(int a, bool na, int b, bool nb) {
        // na and nb signify whether a and b are to be negated 
        a = (a << 1) ^ na, b = (b << 1) ^ nb;
        int neg_a = a ^ 1, neg_b = b ^ 1;
        g[neg_a].push_back(b), g[neg_b].push_back(a);
        trans[b].push_back(neg_a), trans[a].push_back(neg_b);
    }

};

void solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct query {
    int l, r, idx, L, R;
    query(int _l, int _r, int _idx, int _L, int _R) : l(_l), r(_r), idx(_idx), L(_L), R(_R) {}
    bool operator < (const query& other) {
        return l + r < other.l + other.r;
    }
};

struct dsu {
    vector<int> par;
    dsu(int n) {
        par.resize(n + 5);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (x == par[x] ? x : par[x] = find(par[x])); }
    void unite(int a, int b) { par[find(a)] = find(b); }
};

// Problem:
/*
Connected undirected graph of n vertices and m edges
queries L, R, find the minimum k such that all pairs (a, b) l <= a <= b <= r of nodes are reachable
from each other using the first k edges only
*/

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) {
        cin >> u >> v;
        --u, --v;
    }
    vector<query> queries;
    vector<int> query_ans(q);
    for (int i = 0; i < q; i++) {
        int L, R;
        cin >> L >> R;
        if (L == R) continue;
        queries.push_back(query(0, m, i, --L, --R));
    }
    bool did_divide = true;
    while (did_divide) {
        int edges_ptr = -1;
        dsu d(n);
        auto unite_edge = [&](int i) { d.unite(edges[i].first, edges[i].second); };
        did_divide = false;

        vector<int> to_right(n);
        iota(to_right.begin(), to_right.end(), 1); 
        // to_right[i] is the first element that is not in the same component as me
        function<int(int)> nxt = [&](int v) {
            if (to_right[v] == n) return n;
            return (d.find(to_right[v]) == d.find(v) ? to_right[v] = nxt(to_right[v]) : to_right[v]);
        };

        sort(queries.begin(), queries.end());
        for (auto& qu : queries) if (qu.r - qu.l > 1) {
            did_divide = true;
            int mid = qu.r + qu.l >> 1;
            // is it reachable using the first mid edges? 
            while (edges_ptr < mid - 1) unite_edge(++edges_ptr);
            if (nxt(qu.L) > qu.R) qu.r = mid;
            else qu.l = mid;
        }
    }
    for (auto& qu : queries) query_ans[qu.idx] = qu.r;
    for (auto& u : query_ans) cout << u << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}
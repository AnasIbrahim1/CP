#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

const int N = 1e5 + 9;
vector<int> g[N];
int p[N], depth[N], sub[N], tin[N], tout[N], vertex[N], n, timer;

int pre(int v = 1);
void dfs(int v = 1, bool keep = 0);
bool is_ancestor(int u, int v);

void add(int v) {

}

void rem(int v) {

}

void solve_queries(int v) {

}


void solve() {
    cin >> n;
    timer = 0;
    for (int i = 2; i <= n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    pre();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

int pre(int v) {
    tin[v] = ++timer;
    vertex[tin[v]] = v;
    sub[v] = 1;
    for (auto& u : g[v]) if (u != p[v]) {
        depth[u] = depth[v] + 1;
        p[u] = v;
        sub[v] += pre(u);
    }
    tout[v] = timer;
    return sub[v];
}

void dfs(int v, bool keep) {
    int big_child = -1, big_size = 0;
    for (auto& u : g[v]) if (u != p[v] && sub[u] > big_size) {
        big_child = u;
        big_size = sub[u];
    }
    for (auto& u : g[v]) if (u != p[v] && u != big_child) dfs(u, 0);
    if (big_child != -1) dfs(big_child, 1);
    for (auto& u : g[v]) if (u != p[v] && u != big_child) 
        for (int i = tin[u]; i <= tout[u]; i++) add(vertex[i]);
    add(v);
    solve_queries(v);
    if (!keep) for (int i = tin[v]; i <= tout[v]; i++) rem(vertex[i]);
}

bool is_ancestor(int u, int v) {
    return (tin[u] <= tin[v] && tin[v] <= tout[u]);
}

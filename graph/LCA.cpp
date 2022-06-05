#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize "trapv"
#define ll long long
int tt, tc;

const int N = 2e5 + 9;
const int LOG = 20;
vector<int> g[N];
int timer, n, tin[N], tout[N], up[N][LOG];

void dfs(int v, int p) {
    tin[v] = ++timer; up[v][0] = p;
    for (int i = 1; i <= l; ++i) up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto& u : g[v]) if (u != p) dfs(u, v);
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = l; i >= 0; --i) if (!is_ancestor(up[u][i], v)) u = up[u][i];
    return up[u][0];
}

void preprocess(int root) {
    fill(tin, tin + n + 5, 0); fill(tout, tout + n + 5, 0);
    timer = 0;
    for (int i = 0; i <= n + 5; i++) memset(up[i], 0, sizeof(up[i]));
    dfs(root, root);
}

void solve() {
    cin >> n;
    for (int i = 0; i <= n + 5; i++) g[i].clear();
    for (int i = 2; i <= n; i++) {
        // input the edges
    }
    preprocess(1); 
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

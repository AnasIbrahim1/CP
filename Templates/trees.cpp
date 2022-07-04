#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

const int N = 1e5 + 9;
vector<int> g[N];
int p[N], depth[N], sub[N], tin[N], tout[N], vertex[N], n, timer;

int pre(int v = 1);
bool is_ancestor(int u, int v);

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

bool is_ancestor(int u, int v) {
    return (tin[u] <= tin[v] && tin[v] <= tout[u]);
}

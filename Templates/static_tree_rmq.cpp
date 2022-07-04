#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

const int N = 1e5 + 9;
vector<pair<int, int>> g[N];
int p[N], depth[N], sub[N], tin[N], tout[N], vertex[N], n, timer;
const int LOG = 20;
int up[N][LOG], mx[N][LOG], mn[N][LOG];

int pre(int v = 1, int c = INT_MIN);
bool is_ancestor(int u, int v);
int kth(int v, int k);
int lca(int u, int v);
int min_k(int v, int k);
int max_k(int v, int k);
int query_mn(int u, int v);
int query_mx(int u, int v);

void solve() {
    cin >> n;
    timer = 0;
    for (int i = 2; i <= n; i++) {
        int u, v, c; cin >> u >> v >> c;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    pre();
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << query_mn(u, v) << " " << query_mx(u, v) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

int pre(int v, int c) {
    tin[v] = ++timer;
    up[v][0] = (p[v] == 0 ? v : p[v]);
    mx[v][0] = c;
    mn[v][0] = (p[v] == 0 ? -c : c);
    for (int j = 1; j < LOG; j++) {
        up[v][j] = up[up[v][j - 1]][j - 1];
        mx[v][j] = max(mx[v][j - 1], mx[up[v][j - 1]][j - 1]);
        mn[v][j] = min(mn[v][j - 1], mn[up[v][j - 1]][j - 1]);
    }
    vertex[tin[v]] = v;
    sub[v] = 1;
    for (auto& u : g[v]) if (u.first != p[v]) {
        depth[u.first] = depth[v] + 1;
        p[u.first] = v;
        sub[v] += pre(u.first, u.second);
    }
    tout[v] = timer;
    return sub[v];
}


bool is_ancestor(int u, int v) {
    return (tin[u] <= tin[v] && tin[v] <= tout[u]);
}

int kth(int v, int k) {
    for (int bit = 0; bit < LOG; bit++) if ((1 << bit) & k)
        v = up[v][bit];
    return v;
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LOG - 1; i >= 0; i--) 
        if (!is_ancestor(up[u][i], v)) u = up[u][i];
    return up[u][0];
}

int min_k(int v, int k) {
    int ans = INT_MAX;
    for (int bit = 0; bit < LOG; bit++) if ((1 << bit) & k) {
        ans = min(ans, mn[v][bit]);
        v = up[v][bit];
    }
    return ans;
}

int max_k(int v, int k) {
    int ans = INT_MIN;
    for (int bit = 0; bit < LOG; bit++) if ((1 << bit) & k) {
        ans = max(ans, mx[v][bit]);
        v = up[v][bit];
    }
    return ans;
}


int query_mn(int u, int v) {
    if (u == v) return 0;
    int l = lca(u, v);
    return min(min_k(u, depth[u] - depth[l]), min_k(v, depth[v] - depth[l]));
}

int query_mx(int u, int v) {
    if (u == v) return 0;
    int l = lca(u, v);
    return max(max_k(u, depth[u] - depth[l]), max_k(v, depth[v] - depth[l]));
}

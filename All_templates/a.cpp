#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), deg(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    if (m % 2 == 0) return void(cout << 0 << "\n");
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (deg[i] & 1) ans = min(ans, a[i]);
        else {
            int sum = 1e9;
            for (int u : g[i]) if (deg[u] % 2 == 0) sum = min(sum, a[u]);
            sum += a[i];
            ans = min(ans, sum);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}
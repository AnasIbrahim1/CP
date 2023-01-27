#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

ll choose(int n, int r) {
    if (n < r) return 0LL;
    vector<bool> vis(r + 1);
    ll ans = 1;
    for (int i = n - r + 1; i <= n; i++) {
        ans *= i;
        for (int j = 1; j <= r; j++) if (!vis[j] && ans % j == 0) {
            ans /= j;
            vis[j] = true;
        }
    }
    return ans;
}

ll f(int n) {
    ll ans = 0;
    vector<ll> vals = {0, 6, 28, 96, 252};
    vector<ll> poly = { vals[0] , vals[1] - vals[0] };
    for (int i = 2; i < (int)vals.size(); i++) {
        ll new_val = 0;
        for (int j = i; j >= 0; j--) {
            if ((j - i) & 1) new_val -= choose(i, j) * vals[j];
            else new_val += choose(i, j) * vals[j];
        }
        poly.push_back(new_val);
    }
    for (int i = 0; i < (int)poly.size(); i++) 
        ans += poly[i] * choose(n - 1, i);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cout << f(i) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
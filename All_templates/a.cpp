#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];

    map<ll, int> last_seen;
    int l = -1, r = 1e9;
    last_seen[k] = 0;
    for (int i = 1; i <= n; i++) {
        if (last_seen.count(a[i])) {
            int L = last_seen[a[i]], R = i;
            if (R - L < r - l) 
                l = L, r = R;
        }
        last_seen[k + a[i]] = i;
    }
    
    if (l == -1) cout << -1 << "\n";
    else cout << l + 1 << " " << r << "\n";
}

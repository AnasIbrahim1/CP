#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

void solve() {
    int n;
    cin >> n;
    cout << (1 << (2 * n)) << "\n";
    for (int mask = 0; mask < (1 << n); mask++)
        for (int maskp = 0; maskp < (1 << n); maskp++) {
            cout << n << "\n";
            for (int j = 0; j < n; j++) if ((1 << j) & mask) cout << 1;
            else cout << 0;
            cout << "\n";
            for (int j = 0; j < n; j++) if ((1 << j) & maskp) cout << 1;
            else cout << 0;
            cout << "\n";
        }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "w", stdout);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

ifstream in, out1, out2;

int lucky(int x) {
    if (x == 0) return 0;
    int mx = 0, mn = 9;
    while (x > 0) {
        mx = max(mx, x % 10);
        mn = min(mn, x % 10);
        x /= 10;
    }
    return mx - mn;
}


void solve() {
    int l, r;
    cin >> l >> r;
    int x, y;
    out1 >> x;
    out2 >> y;
    assert(x >= l && x <= r);
    assert(y >= l && y <= r);
    if (lucky(x) != lucky(y)) {
        cout << l << " " << r << " " << x << " " << y << "\n";
        exit(0);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.txt", "r", stdin);
    out1.open("output.txt");
    out2.open("output2.txt");
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return a + rng() % (b - a + 1); }

void solve() {
    int n = rand(1, 100000), m = rand(2, 100000);
    int k = rand(1, 100);
    cout << n << " " << m << " " << k << '\n';
    for (int i = 1; i <= n; i++) cout << rand(1, 100000) << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("fortune.in", "w", stdout);
    tt = 1, tc = 1;
    cout << tt << "\n";
    while (tt--) solve(), tc++;
}

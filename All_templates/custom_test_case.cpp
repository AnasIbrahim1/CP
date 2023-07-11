#include <bits/stdc++.h>
using namespace std;


#define ll long long
int tt, tc;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return a + rng() % (b - a + 1); }

void solve() {
    cout << 20 << "\n";
    for (int i = 0; i < 20; i++) cout << rand(0, 1);
    cout << "\n";
    for (int i = 0; i < 20; i++) cout << rand(1, 1000) << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("input.in", "w", stdout);
    tt = 10000, tc = 1;
    cout << tt << "\n";
    while (tt--) solve(), tc++;
}

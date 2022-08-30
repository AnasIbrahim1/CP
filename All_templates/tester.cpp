#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

ifstream AC, WA;

void solve() {
    string ac, wa;
    while (getline(AC, ac)) {
        getline(WA, wa);
        if (ac != wa) return void(cout << "Wrong Answer\n");
    }
    cout << "Accepted\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    AC.open("output_AC.txt");
    WA.open("output_WA.txt");
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

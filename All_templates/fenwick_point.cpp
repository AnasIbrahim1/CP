#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct fenwick_point { 
    int n;
    vector<T> fenw;
    fenwick_point(int _n) : n(_n + 5) { fenw.resize(n); }

    void add(int i, T v) {
        for (++i; i < n; i += (i & -i)) fenw[i] += v;
    }
    T query(int i) {
        T res = 0;
        for (++i; i > 0; i -= (i & -i)) res += fenw[i];
        return res;
    }
};

void solve() {    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct fenwick_range {
    int n;
    vector<T> b1, b2;
    fenwick_range(int _n) : n(_n + 5) {
        b1.resize(n);
        b2.resize(n);
    }
    void add(vector<T>& fenw, int i, T val) {
        for (++i; i < n; i += (i & -i)) fenw[i] += val;        
    }
    void range_add(int l, int r, T val) {
        ++l, ++r;
        add(b1, l, val), add(b1, r + 1, - val);
        add(b2, l, val * (l - 1)), add(b2, r + 1, - val * r);
    }
    T sum(vector<T>& fenw, int i) {
        T res = 0;
        for (++i; i > 0; i -= (i & -i)) res += fenw[i];
        return res;
    }
    T pref_sum(int i) { 
        ++i; 
        return sum(b1, i) * i - sum(b2, i); 
    }
    T range_sum(int l, int r) {
        ++l, ++r;
        return pref_sum(r) - pref_sum(l - 1);
    }
};

void solve() {    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
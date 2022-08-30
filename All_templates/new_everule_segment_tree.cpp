#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

template<typename T>
struct segment_tree {
    int n;
    vector<T> segtree;
    function<T(const T&,const T&)> join;
    T base = T();
    segment_tree(int n, function<T(const T&,const T&)> join, T base = T()) : n(n), join(join), base(base) {
        segtree.resize(n << 1, base);
    }

    T merge(const T& x, const T& y) {
        if (x == base) return y;
        if (y == base) return x;
        return join(x, y);
    }

    void build() {
        for (int i = n - 1; i > 0; --i) 
            segtree[i] = merge(segtree[(i << 1)], segtree[(i << 1) | 1]);
    }

    segment_tree(vector<T> seq, function<T(const T&,const T&)> join, T base = T()) : n(seq.size()), join(join), base(base) {
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) 
            segtree[n + i] = seq[i];
        build();
    }

    void calc(int pos) {
        for (pos >>= 1; pos; pos >>= 1) 
            segtree[pos] = merge(segtree[pos << 1], segtree[pos << 1 | 1]);
    }
    void set(int pos, const T& val) {
        pos += n;
        segtree[pos] = val;
        calc(pos);
    }
    void increment(int pos, const T& val) {
        pos += n;
        segtree[pos] = merge(segtree[pos], val);
        calc(pos);
    }

    T query(int l, int r) {
        T ansl = base, ansr = base;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) 
                ansl = merge(ansl, segtree[l++]);
            if (r & 1)
                ansr = merge(segtree[--r], ansr);
        }
        return merge(ansl, ansr);
    }
};

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

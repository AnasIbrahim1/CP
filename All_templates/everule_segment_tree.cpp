#include <bits/stdc++.h>
using namespace std;


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
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
        }
    }
    segment_tree(vector<T> seq, function<T(const T&,const T&)> join, T base = T()) : n(seq.size()), join(join), base(base) {
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) {
            segtree[n + i] = seq[i];
        }
        build();
    }
    void calc(int pos){
        for (pos >>= 1; pos; pos >>= 1) {
            segtree[pos] = join(segtree[pos << 1], segtree[pos << 1 | 1]);
        }
    }
    void set(int pos, const T& val){
        pos += n;
        segtree[pos] = val;
        calc(pos);
    }
    void increment(int pos, const T& val){
        pos += n;
        segtree[pos] = join(segtree[pos], val);
        calc(pos);
    }

    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                ansl = join(ansl, segtree[l++]);
            }
            if (r & 1) {
                ansr = join(segtree[--r], ansr);
            }
        }
        return join(ansl, ansr);
    }
};

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

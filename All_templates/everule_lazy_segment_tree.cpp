#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

template<typename T, typename U>
struct lazy_segment_tree {
    int n;
    int H;
    T base;
    vector<T> segtree;
    vector<U> lazytree;
    vector<bool> is_empty;
    function<T(const T&, const T&)> join;
    function<T(int, const U&, const T&)> assign;
    function<U(const U&,const U&)> lazyassign;
 
    lazy_segment_tree(vector<T> &seq, 
    function<T(const T&, const T&)> join, 
    function<T(int, const U&, const T&)> assign,
    function<U(const U&,const U&)> lazyassign,
    T base) : join(join), assign(assign), lazyassign(lazyassign), base(base) {
        n = seq.size();
        H = 32 - __builtin_clz(n);
        n = (1 << H);
        segtree.resize(n << 1, base);
        lazytree.resize(n);
        is_empty.resize(n, 1);
        for (int i = 0; i < n; i++) 
            segtree[n + i] = seq[i];
        build();
    }

    void build() {
        for(int i = n - 1; i >= 1; i--) 
            segtree[i] = join(segtree[i << 1], segtree[i << 1 | 1]);
    }

    lazy_segment_tree(int n, 
    function<T(const T&, const T&)> join, 
    function<T(int, const U&, const T&)> assign,
    function<U(const U&,const U&)> lazyassign,
    T base) : n(n), join(join), assign(assign), lazyassign(lazyassign), base(base) {
        H = 32 - __builtin_clz(n);
        n = (1 << H); // may work without it no worries
        segtree.resize(n << 1, base);
        lazytree.resize(n);
        is_empty.resize(n, 1);
    }
    void calc(int pos, int h) {
        segtree[pos] = join(segtree[pos << 1], segtree[pos << 1 | 1]);
        if (!is_empty[pos]) 
            segtree[pos] = assign(h, lazytree[pos], segtree[pos]);
    }

    void apply(int pos, U value, int h) {
        segtree[pos] = assign(h, value, segtree[pos]);
        if (pos < n) {
            if (!is_empty[pos]) 
                lazytree[pos] = lazyassign(value, lazytree[pos]);
            else 
                lazytree[pos] = value;
            is_empty[pos] = 0;
        }
    }

    void update_node(int pos) {
        int h = 0;
        pos += n;
        while (pos > 1) {
            pos >>= 1;
            calc(pos, ++h);
        }
    }

    void push(int pos) {
        int h = H;
        for (pos += n; h; --h) {
            int x = (pos >> h);
            if(!is_empty[x]) {
                apply(x << 1, lazytree[x], h - 1);
                apply(x << 1 | 1, lazytree[x], h - 1);
                is_empty[x] = 1;
            }
        }
    }

    void update_range(int l, int r, U value) {
        push(l), push(r);
        int k = 0;
        int l0 = l, r0 = r;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1, k++) {
            if (l & 1) apply(l++, value, k);
            if (r & 1) apply(--r, value, k);
        }
        update_node(l0);
        update_node(r0);
    }

    T query(int l, int r) {
        push(l), push(r);
        T ansl = base, ansr = base;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ansl = join(ansl, segtree[l++]);
            if (r & 1) ansr = join(segtree[--r], ansr);
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

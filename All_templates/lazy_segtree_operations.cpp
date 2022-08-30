#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct segment_tree_operation {
    int size;
    function<T(const T&, const T&)> operation;
    T base = T();
    vector<T> op;
    segment_tree_operation(int n, function<T(const T&,const T&)> operation, T base = T()) : operation(operation), base(base) {
        size = 1;
        while (size < n) size <<= 1;
        op.resize(size << 1, base);
    }

    T join(const T& x, const T& y) {
        if (x == base) return y;
        if (y == base) return x;
        return operation(x, y);
    }

    void apply_operation(T& x, const T& y) { x = join(x, y); }

    void push(int p) {
        if (p >= size) return;
        apply_operation(op[p << 1], op[p]);
        apply_operation(op[p << 1 | 1], op[p]);
        op[p] = base;
    }

    void apply(int L, int R, const T& v, int p, int l, int r) {
        push(p);
        if (L > r || l > R) return;
        if (L <= l && r <= R) return void(apply_operation(op[p], v));
        int m = l + r >> 1;
        apply(L, R, v, p << 1, l, m);
        apply(L, R, v, p << 1 | 1, m + 1, r);
    }

    void apply(int l, int r, const T& v) { apply(l, r, v, 1, 0, size - 1); }

    T query(int i) { 
        i += size;
        for (int shift = 31 - __builtin_clz(i); shift; shift--)
            push(i >> shift);
        return op[i];
    }
};


void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
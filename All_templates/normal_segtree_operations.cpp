#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct segment_tree_operation {
    int size;
    vector<T> op;
    function<T(const T&,const T&)> operation;
    T base = T();
    segment_tree_operation(int n, function<T(const T&,const T&)> operation, T base = T()) : operation(operation), base(base) {
        size = 1;
        while (size < n) size <<= 1;
        op.resize(size << 1, base);
    }

    void apply(int L, int R, const T& val, int p, int l, int r) {
        if (l > R || L > r) return;
        if (L <= l && r <= R) return void(op[p] = operation(op[p], val));
        int m = l + r >> 1;
        apply(L, R, val, p << 1, l, m);
        apply(L, R, val, p << 1 | 1, m + 1, r);
    }

    void apply(int l, int r, T val) { apply(l, r, val, 1, 0, size - 1); }

    T get(int i, int p, int l, int r) {
        if (l == r) return op[p];
        int m = l + r >> 1;
        if (i <= m) return operation(get(i, p << 1, l, m), op[p]);
        else return operation(get(i, p << 1 | 1, m + 1, r), op[p]);
    }

    T query(int i) { return get(i, 1, 0, size - 1); }
};

void solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

/*
There are two operations here:
modify operation, which we will denote with $
range query operation, which we will denote with #

Needed properties:
1. Both operations need to be associative
2. Modify $ operation needs to be commutative
3. $ is distributive over #, which means that x $ (a # b) = (x $ a) # (x $ b)
*/

template <class T> struct two_operation_segment_tree {
    int size;
    T modify_base = T(), query_base = T();
    vector<T> op, tree;
    function<T(const T&, const T&, int)> modify_oper;
    function<T(const T&, const T&)> query_oper; 

    two_operation_segment_tree(int n, function<T(const T&, const T&, int)> modify_operation, function<T(const T&, const T&)> query_operation, 
                            T modify_base, T query_base) : modify_base(modify_base), query_base(query_base), 
                            modify_oper(modify_operation), query_oper(query_operation) {
        size = 1;
        while (size < n) size <<= 1;
        op.resize(size << 1, modify_base);
        tree.resize(size << 1, query_base);
    }

    T modify_op(const T& x, const T& y, int len) {
        return modify_oper(x, y, len);
    }

    T query_op(const T& x, const T& y) {
        if (x == query_base) return y;
        if (y == query_base) return x;
        return query_oper(x, y);
    }    

    void build_seq(vector<T>& initial_array) {
        for (int i = size; i - size < (int)initial_array.size(); i++)
            tree[i] = initial_array[i - size];
        for (int i = size - 1; i; i--)
            tree[i] = query_op(tree[i << 1], tree[i << 1 | 1]);
    }

    void apply_modify(T& x, const T& y, int len) { x = modify_op(x, y, len); }

    void apply(int L, int R, const T& v, int p, int l, int r) {
        if (l > R || L > r) return;
        if (L <= l && r <= R) {
            apply_modify(op[p], v, 1);
            apply_modify(tree[p], v, r - l + 1);
            return;
        }
        int m = l + r >> 1;
        apply(L, R, v, p << 1, l, m);
        apply(L, R, v, p << 1 | 1, m + 1, r);
        tree[p] = query_op(tree[p << 1], tree[p << 1 | 1]);
        apply_modify(tree[p], op[p], r - l + 1);
    }

    void apply(int l, int r, const T& v) { apply(l, r, v, 1, 0, size - 1); }

    T query(int L, int R, int p, int l, int r) {
        if (l > R || L > r) return query_base;
        if (L <= l && r <= R) return tree[p];
        int m = l + r >> 1;
        T res = query_op(query(L, R, p << 1, l, m), query(L, R, p << 1 | 1, m + 1, r));
        apply_modify(res, op[p], min(R, r) - max(l, L) + 1);
        return res;
    }

    T query(int l, int r) { return query(l, r, 1, 0, size - 1); }
};

void solve() {
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

/*
Properties needed:
1. Commutativity
2. Associativity
*/

template<typename T>
struct segment_tree_operation {
    int n;
    vector<T> op;
    function<T(const T&,const T&)> operation;
    T base = T();
    segment_tree_operation(int n, function<T(const T&,const T&)> operation, T base = T()) : n(n), operation(operation), base(base) {
        op.resize(n << 1, base);
    }

    void apply(int l, int r, const T& val) {
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                op[l] = operation(op[l], val);
                ++l;
            }
            if (r & 1) {
                --r;
                op[r] = operation(op[r], val);
            }
        }
    }

    T query(int i) {
        T ans = base;
        for (i += n; i; i >>= 1) ans = operation(ans, op[i]);
        return ans;
    }
};


void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

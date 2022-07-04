#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

const int N = 1e5 + 9;
int a[N], tree[N << 2], n;

void build(int p = 1, int l = 1, int r = n);
void update(int i, int val, int p = 1, int l = 1, int r = n);
int query(int L, int R, int p = 1, int l = 1, int r = n);

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

void build(int p, int l, int r) {
    if (l == r) return void(tree[p] = a[l]);
    int m = l + r >> 1;
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

void update(int i, int val, int p, int l, int r) {
    if (l == r) return void(tree[p] = a[l]);
    int m = l + r >> 1;
    if (i <= m) update(i, val, p << 1, l, m);
    else update(i, val, p << 1 | 1, m + 1, r);
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

int query(int L, int R, int p, int l, int r) {
    if (L > r || l > R) return 0;
    if (L <= l && r <= R) return tree[p];
    int m = l + r >> 1;
    return max(query(L, R, p << 1, l, m), query(L, R, p << 1 | 1, m + 1, r));
}
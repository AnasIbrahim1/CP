#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

const int N = 1e5 + 9;
const int LOG = 20;
int a[N], lg[N], mn[N][LOG], mx[N][LOG];
int n;
 
void build_sparse();
int query_mn(int l, int r);
int query_mx(int l, int r);
void init_lg();

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build_sparse();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init_lg();
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

void init_lg() {
    lg[0] = lg[1] = 1;
    for (int i = 2; i < N; i++) lg[i] = lg[(i >> 1)] + 1;
}

void build_sparse() {
    for (int i = n; i >= 1; i--) {
        mn[i][0] = a[i];
        mx[i][0] = a[i];
        for (int j = 1; i + (1 << j) - 1 <= n; j++) {
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query_mn(int l, int r) {
    int len = (r - l + 1);
    int L = lg[len] - 1;
    return min(mn[l][L], mn[r - (1 << L) + 1][L]);
}

int query_mx(int l, int r) {
    int len = (r - l + 1);
    int L = lg[len] - 1;
    return max(mx[l][L], mx[r - (1 << L) + 1][L]);
}
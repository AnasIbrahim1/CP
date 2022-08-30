#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 9; // maximum length of string
const int LOG = 20;
int n;
string x;
int p[N], c[N], lcp[N];
int mn[N][LOG];

void suf_arr() {
    x.push_back('$');
    n = x.length();
    // p[i] is the index of the ith suffix in lexiographical sorting
    // c[i] is the class of the suffix starting at i
    for (int i = 0; i < n; i++) p[i] = i;
    sort(p, p + n, [&](int& i, int& j) { return x[i] < x[j]; });
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (x[p[i]] > x[p[i - 1]]);
    int pw = 1;
    for (pw; pw < n; pw *= 2) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - pw + n) % n;
        // --------- count sort -----
        vector<int> cnt(n), pos(n);
        for (int i = 0; i < n; i++) cnt[c[i]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        vector<int> sorted(n);
        for (int i = 0; i < n; i++) sorted[pos[c[p[i]]]++] = p[i];
        for (int i = 0; i < n; i++) p[i] = sorted[i];
        // --------------------------
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int, int> now = { c[p[i]], c[(p[i] + pw) % n] }, before = { c[p[i - 1]], c[(p[i - 1] + pw) % n] };
            c_new[p[i]] = c_new[p[i - 1]] + (now > before);
        }
        for (int i = 0; i < n; i++) c[i] = c_new[i];
    }
}

void build_sparse() {
    for (int i = 1; i < n; i++) mn[i][0] = lcp[i];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < LOG; j++) {
            int new_idx = i + (1 << (j - 1));
            mn[i][j] = min(mn[i][j - 1], (new_idx < n ? mn[new_idx][j - 1] : INT_MAX));
        }
}

void build_lcp() {
    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = c[i];
        int j = p[pi - 1];
        // lcp[i] == lcp(s[i ... ], s[j ... ])
        while (x[i + k] == x[j + k]) k++;
        lcp[pi] = k;
        k = max(k - 1, 0);
    }
}

int LCP(int i, int j) { // longest common prefix of the suffices i and j
    if (i == j) return n - i - 1;
    if (c[i] > c[j]) swap(i, j);
    i = c[i] + 1, j = c[j];
    int len = j - i + 1;
    if (len == 1) return mn[i][0];
    int tmp = 31 - __builtin_clz(len);
    return min(mn[i][tmp], mn[j - (1 << tmp) + 1][tmp]);
}

void solve(int tc) {
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1, tc = 1; // cin >> t;
    while (t--) solve(tc++);
}
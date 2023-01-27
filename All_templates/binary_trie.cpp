#include <bits/stdc++.h>
#include <array>
using namespace std;
#define ll long long
int tt, tc;

struct binary_trie {
    vector<array<int, 2>> trie;
    int LOG;
    binary_trie(int _LOG) : LOG(_LOG) { trie = { array<int, 2>{-1, -1} }; }

    void insert(int x) {
        int v = 0;
        for (int bit = LOG - 1; bit >= 0; --bit) {
            int to = ((1 << bit) & x ? 1 : 0);
            if (~trie[v][to]) v = trie[v][to];
            else {
                v = (trie[v][to] = (int)trie.size());
                trie.push_back(array<int, 2>{-1, -1});
            }        
        }
    }

    int query_max(int x) {
        int v = 0, sum = 0;
        for (int bit = LOG - 1; bit >= 0; bit--) {
            int to = ((1 << bit) & x ? 0 : 1);
            if (~trie[v][to]) v = trie[v][to], sum += to * (1 << bit);
            else v = trie[v][1 - to], sum += (1 - to) * (1 << bit);
        }
        return x ^ sum;
    }

    int query_min(int x) {
        return INT_MAX ^ query_max(INT_MAX ^ x);
    }
};

void solve() {
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

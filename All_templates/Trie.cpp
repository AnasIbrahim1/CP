#include <bits/stdc++.h>
#include <array>
using namespace std;
#define ll long long
int tt, tc;

struct Trie {
    vector<array<int, 26>> trie;
    vector<int> freq;
    array<int, 26> neg;
    Trie() { 
        neg.fill(-1);
        trie = { neg }, freq = { 0 }; 
    }

    void insert(vector<int>& s) {
        int v = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int j = s[i];
            if (~trie[v][j]) v = trie[v][j];
            else {
                v = (trie[v][j] = (int)trie.size());
                trie.push_back(neg), freq.push_back(0);
            }
            freq[v]++;
        }
    }

    int query(vector<int>& s) {
        int v = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int j = s[i];
            if (~trie[v][j]) v = trie[v][j];
            else return i + 1;
        }
        return (int)s.size();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m + 1));
    Trie t;
    for (int i = 0; i < n; i++) {
        vector<int> p(m + 1);
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            p[a[i][j]] = j;
        }
        t.insert(p);
    }
    for (int i = 0; i < n; i++) cout << t.query(a[i]) << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}

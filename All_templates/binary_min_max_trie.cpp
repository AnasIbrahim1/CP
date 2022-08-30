#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct binary_trie {
    int max_bits, max_elements, id;
    vector<vector<pair<int, int>>> trie;
    vector<vector<int>> vis;
    binary_trie() {}

    void resize(int bits, int elements) {
        max_elements = elements + 5;
        max_bits = bits;
        id = 0;
        trie.resize(max_elements * max_bits, vector<pair<int, int>>(2));
        vis.resize(max_elements * max_bits, vector<int>(2));
    }

    void init() { id = 0; }    

    void insert(int x) {
        int cur_node = 0;
        for (int bit = max_bits - 1; bit >= 0; bit--) {
            int next_bit = (((1 << bit) & x) ? 1 : 0);
            if (!(vis[cur_node][next_bit] == tc)) {
                trie[cur_node][next_bit] = {++id, 1};
                vis[cur_node][next_bit] = tc;
            }
            else trie[cur_node][next_bit].second++;
            cur_node = trie[cur_node][next_bit].first;
        }
    }

    int query_max(int x) {
        int cur_node = 0, sum = 0;
        for (int bit = max_bits - 1; bit >= 0; bit--) {
            int next_bit = (((1 << bit) & x) ? 1 : 0);
            if (vis[cur_node][1 - next_bit] == tc) {
                sum += (1 << bit) * (1 - next_bit);
                cur_node = trie[cur_node][1 - next_bit].first;
            }
            else {
                sum += (1 << bit) * next_bit;
                cur_node = trie[cur_node][next_bit].first;
            }
        }
        return (x ^ sum);
    }

    int query_min(int x) {
        int cur_node = 0, sum = 0;
        for (int bit = max_bits - 1; bit >= 0; bit--) {
            int next_bit = (((1 << bit) & x) ? 1 : 0);
            if (vis[cur_node][next_bit] == tc) {
                sum += (1 << bit) * (next_bit);
                cur_node = trie[cur_node][next_bit].first;
            }
            else {
                sum += (1 << bit) * (1 - next_bit);
                cur_node = trie[cur_node][1 - next_bit].first;
            }
        }
        return (x ^ sum);
    }
};

binary_trie trie;
  
void solve() {
    trie.init();
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    trie.resize(17, (1 << 17));
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}
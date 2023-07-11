#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> 
struct sparse_table {
	int n, lg;
	vector<vector<T>> table;
	T base;
	function<T(T, T)> join;
    sparse_table() {}
    void build(const vector<T>& seq, const function<T(T, T)>& _join, T _base) {
        join = _join;
		base = _base;
		n = seq.size() - 1; // 1 based sequence
		lg = 33 - __builtin_clz(n);
		table.resize(n + 5, vector<T>(lg, base));
		for (int i = n; i >= 1; i--) {
			table[i][0] = seq[i];
			for (int j = 1; i + (1 << j) - 1 <= n; j++) 
				table[i][j] = join(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
		}
    }
	sparse_table(const vector<T>& seq, const function<T(T, T)>& _join, T _base) {
		build(seq, _join, _base);
	}

	T query(int l, int r) {
		int len = (r - l + 1);
		int L = 31 - __builtin_clz(len);
		return join(table[l][L], table[r - (1 << L) + 1][L]);
	}

	T query_res(int l, int r) { // restricted
		T res = base;
		int len = (r - l + 1);
		int bit = 0;
		while (l <= r && (1 << bit) <= len) {
			if ((1 << bit) & len) {
				res = join(res, table[l][bit]);
				l += (1 << bit);
			}
			bit++;
		}
		return res;
	}
};


void solve() {
    int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	sparse_table<int> rmq(a, [&](int x, int y) { return min(x, y); }, INT_MAX);
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		++l, ++r;
		cout << rmq.query_res(l, r) << "\n";
	}
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}

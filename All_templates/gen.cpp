#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

int main() {
	freopen("input.txt", "w", stdout);
	int n = 3e5, m = 3e4;
	cout << n << " " << m << "\n";
	for (int i = 0; i < n; i++) cout << rand((int)(-1e5), (int)(1e5)) << " \n"[i == n - 1];
	while (m--) {
		int l = rand(1, n);
		int r = rand(l, n);
		cout << l << " " << r << "\n";
	}
}


#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const int MOD = 1e9 + 7;
int mul(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int modpow(int n, int k);
int divide(int a, int b);

vector<pair<int, int>> poly = { {2, 7}, {3, 22}, {4, 50}, {5, 95} };
vector<int> coeffs;

void pre() {
    coeffs.resize((int)poly.size());
    for (int i = 0; i < (int)poly.size(); i++) {
        coeffs[i] = 1;
        for (int j = 0; j < (int)poly.size(); j++) if (j != i)
            coeffs[i] = mul(coeffs[i], sub(poly[i].first, poly[j].first));
        coeffs[i] = divide(poly[i].second, coeffs[i]);
    }
}

int f(int x) {
    int res = 0;
    for (int i = 0; i < (int)poly.size(); i++) {
        int prod = 1;
        for (int j = 0; j < (int)poly.size(); j++) if (j != i)
            prod = mul(prod, sub(x, poly[j].first));
        prod = mul(prod, coeffs[i]);
        res = add(res, prod);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    cout << mul(2022, f(n)) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    pre();
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

int mul(int a, int b) { return (a * 1LL * b) % MOD; }
int add(int a, int b) { 
	int res = a + b;
	if (res >= MOD) res -= MOD;
	return res;
}
int sub(int a, int b) { return (a - b + MOD) % MOD; }
int divide(int a, int b) { 
	int b_inv = modpow(b, MOD - 2);
	return mul(a, b_inv);
}

int modpow(int n, int k) {
    if (k == 0) return 1;
    int cur = modpow(n, k / 2); cur = mul(cur, cur);
    return (k & 1 ? mul(cur, n) : cur);
}
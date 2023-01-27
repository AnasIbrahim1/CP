#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const int HALF = 499122177;
const int MOD = 998244353;

const int N = 1e7 + 9;
int fact[N], inv[N], inv_fact[N];
int choose(int n, int r);
int mul(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int divide(int a, int b);
int modpow(int n, int k);
vector<int> ntt(vector<int> A, bool inv);
vector<int> convolution(vector<int> A, vector<int> B, int d = -1);

void solve() {
}

void init_fact();
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init_fact();
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

void init_fact() {
    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
	inv[1] = 1;
    for (int i = 2; i < N; i++) {
		fact[i] = mul(i, fact[i - 1]);
		inv[i] = sub(0, mul(MOD / i, inv[MOD % i]));
		inv_fact[i] = mul(inv_fact[i - 1], inv[i]);
	}
}

int mul(int a, int b) { return (a * 1LL * b) % MOD; }
int add(int a, int b) { 
	int res = a + b;
	if (res >= MOD) res -= MOD;
	return res;
}
int sub(int a, int b) { return (a - b + MOD) % MOD; }
int divide(int a, int b) { 
	int b_inv = (b < N ? inv[b] : modpow(b, MOD - 2));
	return mul(a, b_inv);
}

int modpow(int n, int k) {
    if (k == 0) return 1;
    int cur = modpow(n, k / 2); cur = mul(cur, cur);
    return (k & 1 ? mul(cur, n) : cur);
}

int choose(int n, int r) {
    if (n < r) return 0;
    if (r < 0 || n < 0) return 0;
    return mul(fact[n], mul(inv_fact[n - r], inv_fact[r]));
}

vector<int> ntt(vector<int> A, bool inv) {
	int N = A.size();
	int r = 3;
	if (inv) r = divide(1, r);
	vector<int> B(N);
	for (int i = N / 2; i > 0; i /= 2) {
		int z = modpow(r, (MOD - 1) / (N / i));
		int z2 = 1;
		for (int j = 0; j < N; j += (i << 1)){
			for (int k = 0; k < i; k++){
				A[i + j + k] = mul(A[i + j + k], z2);
				B[(j >> 1) + k] = add(A[j + k], A[i + j + k]);
				B[(N >> 1) + (j >> 1) + k] = sub(A[j + k], A[i + j + k]);
			}
            z2 = mul(z2, z);
		}
		swap(A, B);
	}
	if (inv) {
		int Ninv = divide(1, N);
		for (int i = 0; i < N; i++)
			A[i] = mul(A[i], Ninv);
	}
	return A;
}

vector<int> convolution(vector<int> A, vector<int> B, int d) {
	int deg = A.size() + B.size() - 1;
	int N = 1;
	while (N < deg) N <<= 1;
	A.resize(N), B.resize(N);
	A = ntt(A, false), B = ntt(B, false);
	vector<int> ans(N);
	for (int i = 0; i < N; i++)
        ans[i] = mul(A[i], B[i]);
	ans = ntt(ans, true);
	if (d != -1) deg = d;
	ans.resize(deg);
	return ans;
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const int HALF = 499122177;
const int MOD = 998244353;
int add(int a, int b) {
    int res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}
int mul(int a, int b) { return (a * 1LL * b) % MOD; }
int ex(int n, int k) {
    int ans = 1;
    while (k) {
        if (k & 1) ans = mul(ans, n);
        n = mul(n, n);
        k >>= 1;
    }
    return ans;
}
int sub(int a, int b) { return add(a - b, MOD); }
int divide(int a, int b) { return mul(a, ex(b, MOD - 2)); }
int modinv(int x) { return divide(1, x); }

vector<int> ntt(vector<int> A, bool inv){
	int N = A.size();
	int r = 3;
	if (inv) r = modinv(r);
	
    vector<int> B(N);
	for (int i = N / 2; i > 0; i /= 2){
		int z = ex(r, (MOD - 1) / (N / i));
		int z2 = 1;
		for (int j = 0; j < N; j += i * 2){
			for (int k = 0; k < i; k++){
				A[i + j + k] = mul(A[i + j + k], z2);
				B[j / 2 + k] = add(A[j + k], A[i + j + k]);
				B[N / 2 + j / 2 + k] = sub(A[j + k], A[i + j + k]);
			}
            z2 = mul(z2, z);
		}
		swap(A, B);
	}
	if (inv) {
		int Ninv = modinv(N);
		for (int i = 0; i < N; i++)
            A[i] = mul(A[i], Ninv);
	}
	return A;
}

vector<int> convolution(vector<int> A, vector<int> B, int d = -1){
	int deg = A.size() + B.size() - 1;
	int N = 1;
	while (N < deg) N <<= 1;
	A.resize(N), B.resize(N);
	A = ntt(A, false), B = ntt(B, false);

	vector<int> ans(N);
	for (int i = 0; i < N; i++) ans[i] = mul(A[i], B[i]);

	ans = ntt(ans, true);
	if (d != -1) deg = d;

	ans.resize(deg);
	return ans;
}

const int N = 4e5 + 9;
int fact[N], inv_fact[N];
void calc_fact();
int choose(int n, int r);

void solve() {
    int n, m;
    cin >> n >> m;
    if (n > m) swap(n, m);
    vector<int> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; i++) {
        a[i] = mul(inv_fact[i], inv_fact[i + m - n]);
        b[i] = inv_fact[i];
    }
    vector<int> c = convolution(a, b);
    vector<int> w(n + 1);
    for (int i = 0; i <= n; i++) {
        w[i] = mul(fact[n - i], fact[m - i]);
        w[i] = mul(w[i], c[n - i]);
    }
    for (int i = 0; i <= n; i++) {
        if (i & 1) 
            a[i] = sub(0, mul(w[i], inv_fact[i]));
        else
            a[i] = mul(w[i], inv_fact[i]);
    }
    c = convolution(a, b);
    vector<int> q(n + 1);
    for (int i = 0; i <= n; i++) q[i] = mul(fact[i], c[i]);
    vector<int> k(n + 1);
    for (int i = 0; i <= n; i++) k[i] = mul(choose(n, i), choose(m, i));
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        // cout << k[i] << "\n";
        ans = add(ans, mul(k[i], q[i]));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    calc_fact();
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}

void calc_fact() {
    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
    for (int i = 2; i < N; i++) {
        fact[i] = mul(i, fact[i - 1]);
        inv_fact[i] = modinv(fact[i]);
    }
}

int choose(int n, int r) {
    if (n < r) return 0;
    if (r < 0 || n < 0) return 0;
    return mul(fact[n], mul(inv_fact[n - r], inv_fact[r]));
}

/*
Let f(x, y, k)
*/
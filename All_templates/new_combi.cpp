#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const ll HALF = 499122177;
const ll MOD = 998244353;

const int N = 2e5 + 9;
ll fact[N], inv[N], inv_fact[N];
ll choose(ll n, ll r);
ll mul(ll a, ll b);
ll add(ll a, ll b);
ll sub(ll a, ll b);
ll divide(ll a, ll b);
ll modpow(ll n, ll k);
vector<ll> ntt(vector<ll> A, bool inv);
vector<ll> convolution(vector<ll> A, vector<ll> B, int d = -1);

void solve() {

}

void init_fact();
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init_fact();
    tt = 1, tc = 1; //cin >> tt;
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

ll mul(ll a, ll b) { return (a * b) % MOD; }
ll add(ll a, ll b) { return (a + b) % MOD; }
ll sub(ll a, ll b) { return (a - b + MOD) % MOD; }
ll divide(ll a, ll b) { 
	ll b_inv = (b < N ? inv[b] : modpow(b, MOD - 2));
	return mul(a, b_inv);
}

ll modpow(ll n, ll k) {
    if (k == 0) return 1;
    ll cur = modpow(n, k / 2); cur = mul(cur, cur);
    return (k & 1 ? mul(cur, n) : cur);
}

ll choose(ll n, ll r) {
    if (n < r) return 0;
    if (r < 0 || n < 0) return 0;
    return mul(fact[n], mul(inv_fact[n - r], inv_fact[r]));
}

vector<ll> ntt(vector<ll> A, bool inv) {
	int N = A.size();
	ll r = 3;
	if (inv) r = divide(1, r);
	vector<ll> B(N);
	for (int i = N / 2; i > 0; i /= 2) {
		ll z = modpow(r, (MOD - 1) / (N / i));
		ll z2 = 1;
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

vector<ll> convolution(vector<ll> A, vector<ll> B, int d) {
	int deg = A.size() + B.size() - 1;
	int N = 1;
	while (N < deg) N <<= 1;
	A.resize(N), B.resize(N);
	A = ntt(A, false), B = ntt(B, false);
	vector<ll> ans(N);
	for (int i = 0; i < N; i++)
        ans[i] = mul(A[i], B[i]);
	ans = ntt(ans, true);
	if (d != -1) deg = d;
	ans.resize(deg);
	return ans;
}
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct poly {
	using cd = complex<double>;
	const double PI = acos(-1);
	const static int MX = 2 * (56e4 + 9);
	cd pre_w[MX], pre_w_inv[MX];
	bool is_w_const;
	int pw_2;
	poly() : is_w_const(false) {}

	void pre() {
		if (is_w_const) return;
		is_w_const = true;
		pw_2 = 1;
		while ((pw_2 << 1) < MX) pw_2 <<= 1;
		for (int j = 0; j < pw_2; j++) {
			double ang = j * 2 * PI / pw_2;
			pre_w[j] = cd(cos(ang), sin(ang));
			pre_w_inv[j] = cd(cos(-ang), sin(-ang));
		}
	}

	void fft(vector<cd>& a, bool invert) {
		pre();
		int n = a.size();

		for (int i = 1, j = 0; i < n; i++) {
			int bit = n >> 1;
			for (; j & bit; bit >>= 1) j ^= bit;
			j ^= bit;

			if (i < j) swap(a[i], a[j]);
		}

		for (int len = 2; len <= n; len <<= 1) 
			for (int i = 0; i < n; i += len) 
				for (int j = 0; j < len / 2; j++) {
					int k = (pw_2/len) * j;
					cd w = (invert ? pre_w_inv[k] : pre_w[k]);
					cd u = a[i + j], v = a[i + j + (len >> 1)] * w;
					a[i + j] = u + v;
					a[i + j + (len >> 1)] = u - v;
				}

		if (invert) for (cd& x : a) x /= n;
	}

	vector<T> convolve(vector<T> const &a, vector<T> const &b) {
		vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
		int n = 1;
		while (n < a.size() + b.size()) n <<= 1;
		fa.resize(n), fb.resize(n);
	
		fft(fa, false), fft(fb, false);
		for (int i = 0; i < n; i++) fa[i] *= fb[i];
		fft(fa, true);
	
		vector<T> result(n);
		for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
		return result;
	}

	ll mod;
	ll add(ll x, ll y) { return (x + y) % mod; }
	ll mul(ll x, ll y) { return (x * y) % mod; }
	vector<ll> convolve_mod(const vector<ll>& a, const vector<ll>& b) {
		ll sq = (ll)sqrt(mod);
		int n = a.size(), m = b.size();
		vector<ll> a_0(n), a_1(n), b_0(m), b_1(m);

		for (int i = 0; i < n; i++) 
			a_0[i] = a[i] % sq, a_1[i] = a[i] / sq;

		for (int i = 0; i < m; i++) 
			b_0[i] = b[i] % sq, b_1[i] = b[i] / sq;

		auto a_0b_0 = convolve(a_0, b_0);
		auto a_0b_1 = convolve(a_0, b_1);
		auto a_1b_0 = convolve(a_1, b_0);
		auto a_1b_1 = convolve(a_1, b_1);
		
		// (a_0 + a_1 sq)(b_0 + b_1 sq) = a_0b_0 + sq(a_0b_1 + a_1b_0) + a_1b_1 sq^2
		vector<ll> res(n + m - 1);
		for (int i = 0; i < n + m - 1; i++) {
			if (i < (int)a_0b_0.size()) {
				a_0b_0[i] %= mod;
				res[i] = add(res[i], a_0b_0[i]);
			}
			ll mid_addition = 0;
			if (i < (int)a_0b_1.size()) mid_addition = add(mid_addition, a_0b_1[i] % mod);
			if (i < (int)a_1b_0.size()) mid_addition = add(mid_addition, a_1b_0[i] % mod);
			mid_addition = mul(sq, mid_addition);
			res[i] = add(res[i], mid_addition);
			if (i < (int)a_1b_1.size()) res[i] = add(res[i], mul(a_1b_1[i] % mod, mul(sq, sq)));
		}
		return res;
	}
};

poly<ll> me;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<ll> a(n), b(m);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int j = 0; j < m; j++) cin >> b[j];
	auto res = me.convolve(a, b);
	for (int i = 0; i < n + m - 1; i++) 
		cout << (i < (int)res.size() ? res[i] : 0) << " ";
	cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}	
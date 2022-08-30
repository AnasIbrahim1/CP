#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct poly_mult {
    int mod = 998244353;
    int mul(int a, int b) { return ((ll)a * b) % mod; }
    int add(int a, int b) { 
        int res = a + b;
        if (res >= mod) res -= mod;
        return res;
    }
    int sub(int a, int b) { return add(a - b, mod); }
    int modpow(int a, int b) {
        int ans = 1;
        while (b) {
            if (b & 1) ans = mul(ans, a);
            a = mul(a, a);
            b >>= 1;
        }
        return ans;
    }
    ll modinv(ll a) { return modpow(a, mod - 2); }
    vector<int> ntt(vector<int> A, bool inv) {
        int N = A.size();
        int r = 3;
        if (inv) r = modinv(r);
        vector<int> B(N);
        for (int i = N / 2; i > 0; i /= 2) {
            int z = modpow(r, (mod - 1) / (N / i));
            int z2 = 1;
            for (int j = 0; j < N; j += i * 2) {
                for (int k = 0; k < i; k++) {
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
            for (int i = 0; i < N; i++)  A[i] = mul(A[i], Ninv);
        }
        return A;
    }
    vector<int> convolution(vector<int> A, vector<int> B, int d = -1) {
        int deg = A.size() + B.size() - 1;
        int N = 1;
        while (N < deg) N <<= 1;
        A.resize(N);
        B.resize(N);
        A = ntt(A, false);
        B = ntt(B, false);
        vector<int> ans(N);
        for (int i = 0; i < N; i++) ans[i] = mul(A[i], B[i]);
        ans = ntt(ans, true);
        if (d != -1) deg = d;
        ans.resize(deg);
        return ans;
    }
};
poly_mult pp;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& u : a) cin >> u;
    for (auto& u : b) cin >> u;
    auto ans = pp.convolution(a, b);
    for (auto& u : ans) cout << u << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}
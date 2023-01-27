#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const int HALF = 499122177;
const int MOD = 998244353;

const int N = 3e5 + 9;
int fact[N], inv[N], inv_fact[N];
int choose(int n, int r);
int mul(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int divide(int a, int b);
int modpow(int n, int k);
vector<int> ntt(vector<int> A, bool inv);
vector<int> convolution(vector<int> A, vector<int> B, int d = -1);

struct relaxed_convolution {
  int N;
  vector<int> A, B, C;
  relaxed_convolution(): N(0){
  }
  int query(int a, int b) {
    A.push_back(a);
    B.push_back(b);
    C.push_back(0);
    if (N > 0){
      C.push_back(0);
    }
    int p = __builtin_ctz(N + 2);
    for (int j = 0; j <= p; j++){
      vector<int> a1(1 << j);
      for (int k = 0; k < (1 << j); k++)
        a1[k] = A[(1 << j) - 1 + k];
      vector<int> b1(1 << j);
      for (int k = 0; k < (1 << j); k++)
        b1[k] = B[N - ((1 << j) - 1 - k)];
      vector<int> c1 = convolution(a1, b1);
      for (int k = 0; k < (1 << (j + 1)) - 1; k++)
        C[N + k] = add(C[N + k], c1[k]);
      if ((1 << p) == N + 2 && j == p - 1)
        break;
      vector<int> a2(1 << j);
      for (int k = 0; k < (1 << j); k++)
        a2[k] = A[N - ((1 << j) - 1 - k)];
      vector<int> b2(1 << j);
      for (int k = 0; k < (1 << j); k++)
        b2[k] = B[(1 << j) - 1 + k];
      vector<int> c2 = convolution(a2, b2);
      for (int k = 0; k < (1 << (j + 1)) - 1; k++)
        C[N + k] = add(C[N + k], c2[k]);
    }
    N++;
    return C[N - 1];
  }
};

void solve() {
    int n;
    cin >> n;
    vector<int> P(n + 1);
    // P[s] is the number of red-connected graphs that has no subgraphs that are both red and blue connected
    // Q[s] is the number of blue-connected graphs that has no subgraphs that are both red and blue connected
    // 1 node is red connected but not blue connected by definition
    /*
        (s - 1)! * { P[k] / (k - 1)! } * { (2P[s - k])/(s - k)! }
    */
    // A[k] = P[k]/(k - 1)!
    // B[k] = 2P[k]/k!
    // P[s] = (s - 1)! * (A[1]B[s - 1] + A[2]B[s - 2] + ... + A[s - 1]B[1])
    auto A = [&](int k) {
        if (k <= 2) return min(k, 1);
        return mul(P[k], inv_fact[k - 1]);
    };
    auto B = [&](int k) {
        if (k <= 2) return min(k, 1);
        return mul(add(P[k], P[k]), inv_fact[k]);
    };
    
    relaxed_convolution RC;
    for (int s = 2; s <= n; s++) P[s] = mul(fact[s - 1], RC.query(A(s - 1), B(s - 1)));

    cout << sub(add(P[n], P[n]), 2) << "\n";
}

void init_fact();
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init_fact();
    tt = 1, tc = 1; // cin >> tt;
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
        for (int j = 0; j < N; j += (i << 1)) {
            for (int k = 0; k < i; k++) {
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

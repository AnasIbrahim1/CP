#include <bits/stdc++.h>
using namespace std;


#define ll long long
int tt, tc;

// COMBINATORICS TEMPLATE
const ll mod = 1e9 + 7;
ll mul(ll a, ll b);
ll add(ll a, ll b);
ll sub(ll a, ll b);
ll divide(ll a, ll b);
ll binexp(ll n, ll k);

const int N = 2e5 + 9;
ll fact[N];
ll choose(ll n, ll r);
ll stars_and_bars(ll stars, ll bars);

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
    fact[0] = fact[1] = 1;
    for (int i = 2; i < N; i++) fact[i] = mul(i, fact[i - 1]);
}

ll mul(ll a, ll b) { return (a * b) % mod; }
ll add(ll a, ll b) { return (a + b) % mod; }
ll sub(ll a, ll b) { return (a - b + mod) % mod; }
ll divide(ll a, ll b) { return mul(a, binexp(b, mod - 2)); }

ll binexp(ll n, ll k) {
    if (k == 0) return 1;
    ll cur = binexp(n, k / 2); cur = mul(cur, cur);
    return (k & 1 ? mul(cur, n) : cur);
}

ll choose(ll n, ll r) {
    if (n < r) return 0;
    if (r < 0 || n < 0) return 0;
    return divide(fact[n], mul(fact[n - r], fact[r]));
}

ll stars_and_bars(ll stars, ll bars) { return choose(stars + bars, bars); }
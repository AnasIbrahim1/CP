#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

const int N = 1e7 + 9;

ll phi[N], f[N], cnt[N], spf[N], spf_pw[N];
vector<int> primes;
// f[i] = sum d | i d phi[d]
// f[p^k] = f[p^{k - 1}] + p^k * phi[p^k]

void linear_sieve() {
    iota(spf, spf + N, 0);
	f[1] = 1;
    for (int i = 2; i < N; i++) {
        if (spf[i] == i) {
            spf_pw[i] = i, cnt[i] = 1, phi[i] = i - 1, f[i] = 1 + i * 1LL * (i - 1);
            primes.push_back(i);
        }
        for (auto& prime : primes) {
            if (i * 1LL * prime >= N) break;
            spf[i * prime] = prime;
            if (i % prime == 0) {
                cnt[i * prime] = 1 + cnt[i], spf_pw[i * prime] = prime * spf_pw[i], phi[i * prime] = prime * phi[i];
				int prime_pw = spf_pw[i * prime], rest = i / spf_pw[i];
				f[i * prime] = f[rest] * (f[prime_pw / prime] + prime_pw * 1LL * phi[prime_pw]);
				break;
            } else {
                cnt[i * prime] = 1, spf_pw[i * prime] = prime, phi[i * prime] = phi[i] * phi[prime];
				f[i * prime] = f[i] * f[prime];
            }
        }
    }
}

// f[n] = sum {i = 1}^{n} n/gcd(i, n)

void solve() {
    int n;
	cin >> n;
	cout << f[n] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	linear_sieve();
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize ("O3")
#define ll long long
int tt, tc;

// NUMBER THEORY TEMPLATE
const int N = 2e6 + 9;
int spf[N]; // smallest prime factor

void sieve();
vector<pair<int, int>> p_factor(int x);
ll sum_divs(const vector<pair<int, int>>& pfact);
int num_divs(const vector<pair<int, int>>& pfact);
void brute_divs(int, int, const vector<pair<int, int>>&);
vector<int> find_divs(const vector<pair<int, int>>& p_fact);

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    sieve();
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

void sieve() {
    spf[0] = spf[1] = 1;
    for(int i = 2; i < N; i++) spf[i] = i;
    for (int i = 2; i <= N / i; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

vector<pair<int, int>> p_factor(int x) {
    vector<pair<int, int>> ret;
    while (x > 1) {
        if (ret.empty() || spf[x] != ret.back().first) ret.emplace_back(spf[x], 1);
        else ret.back().second++;
        x /= spf[x];
    }
    return ret;
}

ll sum_divs(const vector<pair<int, int>>& pfact) {
    if (pfact.empty()) return 1;
    ll prod = 1;
    for (auto& u : pfact) {
        ll pw = u.first;
        for (int i = 0; i < u.second; i++) pw *= (ll)u.first;
        pw -= 1;
        pw /= (ll)(u.first - 1);
        prod *= pw;
    }
    return prod;
}

int num_divs(const vector<pair<int, int>>& pfact) {
    int prod = 1;
    for (auto& u : pfact) prod *= (u.second + 1);
    return prod;
}

vector<int> divs_glob;
void brute_divs(int idx, int prod_so_far, const vector<pair<int, int>>& prime_fact) {
    if (idx == prime_fact.size()) {
        divs_glob.emplace_back(prod_so_far);
        return;
    }
    int p_pow = 1;
    for (int i = 0; i <= prime_fact[idx].second; i++) {
        brute_divs(idx + 1, p_pow * prod_so_far, prime_fact);
        if (i < prime_fact[idx].second) p_pow *= prime_fact[idx].first;
    }
}

vector<int> find_divs(const vector<pair<int, int>>& p_fact) {
    if (p_fact.empty()) return {1};
    divs_glob.clear();
    brute_divs(0, 1, p_fact);
    sort(divs_glob.begin(), divs_glob.end());
    return divs_glob;
}

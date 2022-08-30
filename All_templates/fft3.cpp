#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

#define ld long double
struct FFT {
 
    const int maxk = 21, maxn = (1 << maxk) + 1;
    const ld PI = acos(-1);
    vector<ld> wR, wI, rR, rI, aR, aI;
    vector<ll> dp;
    int n, k, lastk;
    FFT() {
        lastk = -1;
        wR.resize(maxn);
        wI.resize(maxn);
        rR.resize(maxn);
        rI.resize(maxn);
        aR.resize(maxn);
        aI.resize(maxn);
        dp.resize(maxn);
    }
    void fft(bool inv) {
        if(lastk != k) {
            lastk = k;
            dp[0] = 0;
            for(int i = 1, g = -1; i < n; ++i) {
                if((i & (i - 1)) == 0) ++g;
                dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
            }
            wR[1] = 1;
            wI[1] = 0;
            for(int t = 0; t < k - 1; ++t) {
                ld a = PI / n * (1 << (k - 1 - t));
                ld curR = cos(a), curI = sin(a);
                int p2 = (1 << t), p3 = p2 * 2;
                for(int j = p2, k = j * 2; j < p3; ++j, k += 2) {
                    wR[k] = wR[j], wI[k] = wI[j];
                    wR[k + 1] = wR[j] * curR - wI[j] * curI;
                    wI[k + 1] = wR[j] * curI + wI[j] * curR;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            ll d = dp[i];
            if(i < d) {
                swap(aR[i], aR[d]);
                swap(aI[i], aI[d]);
            }
        }
        if(inv) {
            for(int i = 0; i < n; ++i) {
                aI[i] = -aI[i];
            }
        }
        for(int len = 1; len < n; len <<= 1) {
            for(int i = 0; i < n; i += len) {
                int wit = len;
                for(int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
                    ld tmpR = aR[j] * wR[wit] - aI[j] * wI[wit];
                    ld tmpI = aR[j] * wI[wit] + aI[j] * wR[wit];
                    wit++;
                    aR[j] = aR[i] - tmpR;
                    aI[j] = aI[i] - tmpI;
                    aR[i] += tmpR;
                    aI[i] += tmpI;
                }
            }
        }
    }
    vector<ll> multiply(vector<ll> a, vector<ll> b) {
        int na = (int) a.size(), nb = (int) b.size();
        for(k = 0, n = 1; n < na + nb - 1; n <<= 1, k++);
        for(int i = 0; i < n; ++i) {
            aR[i] = i < na ? a[i] : 0;
            aI[i] = i < nb ? b[i] : 0;
        }
        fft(false);
        aR[n] = aR[0];
        aI[n] = aI[0];
        ld q = -1.0 / n / 4.0;
        for(int i = 0; i <= n - i; ++i) {
            ld tmpR = aR[i] * aR[i] - aI[i] * aI[i];
            ld tmpI = aR[i] * aI[i] * 2;
            tmpR -= aR[n - i] * aR[n - i] - aI[n - i] * aI[n - i];
            tmpI -= aR[n - i] * aI[n - i] * -2;
            aR[i] = -tmpI * q;
            aI[i] = tmpR * q;
            aR[n - i] = aR[i];
            aI[n - i] = -aI[i];
        }
        fft(true);
        vector<ll> ans(n = na + nb - 1);
        for(int i = 0; i < n; ++i) {
            ans[i] = round(aR[i]);
        }
        return ans;
    }
};
// careful, you may access something that is out of bounds to the vector, you then output 0 instead

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; // cin >> tt;
    while (tt--) solve(), tc++;
}
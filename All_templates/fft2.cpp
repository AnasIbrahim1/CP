#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

using cd = complex<double>;
const double PI = acos(-1);
ll reverse(ll num, ll lg_n) {
    ll res = 0;
    for (ll i = 0; i < lg_n; i++) {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    return res;
}
 
void fft(vector<cd> &a, bool invert) {
    ll n = a.size();
    ll lg_n = 0;
    while ((1 << lg_n) < n)
        lg_n++;
 
    for (ll i = 0; i < n; i++) {
        if (i < reverse(i, lg_n))
            swap(a[i], a[reverse(i, lg_n)]);
    }
 
    for (ll len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd &x : a)
            x /= n;
    }
}
 
vector<ll> multiply(vector<ll> const &a, vector<ll> const &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<ll> result(n);
    for (ll i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
// careful, you may access something that is out of bounds to the vector, you then output 0 instead


void solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}
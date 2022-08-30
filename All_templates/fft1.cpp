#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

namespace FFT {
    using Complex = complex<double>;
    const double PI = acos(-1);
 
    void DiscreteFourier(vector<Complex>& a, bool invert) {
        int n = a.size();
        if (n == 1) return;
        vector<Complex> a0(n / 2), a1(n / 2);
        for (int i = 0; 2 * i < n; i++) {
            a0[i] = a[2 * i];
            a1[i] = a[2 * i + 1];
        }
        DiscreteFourier(a0, invert), DiscreteFourier(a1, invert);
        double ang = 2 * PI / n * (invert ? -1 : 1);
        Complex w(1), wn(cos(ang), sin(ang));
        for (int i = 0; 2 * i < n; i++) {
            a[i] = a0[i] + w * a1[i];
            a[i + n / 2] = a0[i] - w * a1[i];
            if (invert) {
                a[i] /= 2;
                a[i + n / 2] /= 2;
            }
            w *= wn;
        }
    }

    template <class T> 
    vector<T> mul(vector<int> const& a, vector<int> const& b) {
        vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size()) n <<= 1;
        fa.resize(n);
        fb.resize(n);
        DiscreteFourier(fa, false);
        DiscreteFourier(fb, false);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        DiscreteFourier(fa, true);
        vector<T> result(n);
        for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
        return result;
    }
};
// careful, you may access something that is out of bounds to the vector, you then output 0 instead

void solve() {
        
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}
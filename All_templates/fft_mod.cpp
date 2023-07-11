/**
* Paliukh RED_INSIDE 10.2022-
*/
#ifdef ONPC
#define _GLIBCXX_DEBUG
#else
#pragma GCC optimize("O3")
#pragma unroll
#endif

#include <bits/stdc++.h>
using namespace std;
int tt, tc;
typedef long long ll;
typedef long double ld;

namespace fft {
    typedef long double real;

    /**
     * complex number
     */
    struct Num {
        real x, y;

        Num() { x = y = 0; }

        Num(real x_, real y_) : x(x_), y(y_) {}
    };

    inline Num operator+(Num a, Num b) {
        return Num(a.x + b.x, a.y + b.y);
    }

    inline Num operator-(Num a, Num b) {
        return Num(a.x - b.x, a.y - b.y);
    }

    inline Num operator*(Num a, Num b) {
        return Num(a.x * b.x - a.y * b.y,
                   a.x * b.y + a.y * b.x);
    }

    inline Num conj(Num a) {
        return Num(a.x, -a.y);
    }

    int base = 1;
    vector<Num> roots = {{0, 0},
                         {1, 0}};
    vector<int> rev = {0, 1};
    const real PI = static_cast<real>(acosl(-1.0));

    void EnsureBase(int nbase) {
        if (nbase <= base) {
            return;
        }
        rev.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            real angle = 2 * PI / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                real angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = Num(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }

    void FFT(vector<Num> &a, int n = -1) {
        if (n == -1) {
            n = (int) a.size();
        }
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        EnsureBase(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    Num z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    vector<Num> fa, fb;


    /* optional */
    vector<int64_t> Square(const vector<int> &a) {
        if (a.empty()) {
            return {};
        }
        int need = (int) a.size() + (int) a.size() - 1;
        int nbase = 1;
        while ((1 << nbase) < need) nbase++;
        EnsureBase(nbase);
        int sz = 1 << nbase;
        if ((sz >> 1) > (int) fa.size()) {
            fa.resize(sz >> 1);
        }
        for (int i = 0; i < (sz >> 1); i++) {
            int x = (2 * i < (int) a.size() ? a[2 * i] : 0);
            int y = (2 * i + 1 < (int) a.size() ? a[2 * i + 1] : 0);
            fa[i] = Num(x, y);
        }
        FFT(fa, sz >> 1);
        Num r(1.0 / (sz >> 1), 0.0);
        for (int i = 0; i <= (sz >> 2); i++) {
            int j = ((sz >> 1) - i) & ((sz >> 1) - 1);
            Num fe = (fa[i] + conj(fa[j])) * Num(0.5, 0);
            Num fo = (fa[i] - conj(fa[j])) * Num(0, -0.5);
            Num aux = fe * fe + fo * fo * roots[(sz >> 1) + i] * roots[(sz >> 1) + i];
            Num tmp = fe * fo;
            fa[i] = r * (conj(aux) + Num(0, 2) * conj(tmp));
            fa[j] = r * (aux + Num(0, 2) * tmp);
        }
        FFT(fa, sz >> 1);
        vector<int64_t> res(need);
        for (int i = 0; i < need; i++) {
            res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
        }
        return res;
    }

    vector<int64_t> PolyMult(const vector<int> &a, const vector<int> &b) {
        if (a.empty() || b.empty()) {
            return {};
        }
        if (a == b) {
            return Square(a);
        }
        int need = (int) a.size() + (int) b.size() - 1;
        int nbase = 1;
        while ((1 << nbase) < need) nbase++;
        EnsureBase(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size()) {
            fa.resize(sz);
        }
        for (int i = 0; i < sz; i++) {
            int x = (i < (int) a.size() ? a[i] : 0);
            int y = (i < (int) b.size() ? b[i] : 0);
            fa[i] = Num(x, y);
        }
        FFT(fa, sz);
        Num r(0, -0.25 / (sz >> 1));
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            Num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            fa[i] = z;
        }
        for (int i = 0; i < (sz >> 1); i++) {
            Num A0 = (fa[i] + fa[i + (sz >> 1)]) * Num(0.5, 0);
            Num A1 = (fa[i] - fa[i + (sz >> 1)]) * Num(0.5, 0) * roots[(sz >> 1) + i];
            fa[i] = A0 + A1 * Num(0, 1);
        }
        FFT(fa, sz >> 1);
        vector<int64_t> res(need);
        for (int i = 0; i < need; i++) {
            res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
        }
        return res;
    }

    vector<int> PolyMultMod(const vector<int> &a, const vector<int> &b, int md) {
        if (a.empty() || b.empty()) {
            return {};
        }
        int eq = (a.size() == b.size() && a == b);
        int need = (int) a.size() + (int) b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        EnsureBase(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size()) {
            fa.resize(sz);
        }
        for (int i = 0; i < (int) a.size(); i++) {
            int x = (a[i] % md + md) % md;
            fa[i] = Num(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, Num{0, 0});
        FFT(fa, sz);
        if (sz > (int) fb.size()) {
            fb.resize(sz);
        }
        if (eq) {
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        } else {
            for (int i = 0; i < (int) b.size();
                 i++) {
                int x = (b[i] % md + md) % md;
                fb[i] = Num(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, Num{0, 0});
            FFT(fb, sz);
        }
        real ratio = 0.25 / sz;
        Num r2(0, -1);
        Num r3(ratio, 0);
        Num r4(0, -ratio);
        Num r5(0, 1);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            Num a1 = (fa[i] + conj(fa[j]));
            Num a2 = (fa[i] - conj(fa[j])) * r2;
            Num b1 = (fb[i] + conj(fb[j])) * r3;
            Num b2 = (fb[i] - conj(fb[j])) * r4;
            if (i != j) {
                Num c1 = (fa[j] + conj(fa[i]));
                Num c2 = (fa[j] - conj(fa[i])) * r2;
                Num d1 = (fb[j] + conj(fb[i])) * r3;
                Num d2 = (fb[j] - conj(fb[i])) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        FFT(fa, sz);
        FFT(fb, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++) {
            int64_t aa = llround(fa[i].x);
            int64_t bb = llround(fb[i].x);
            int64_t cc = llround(fa[i].y);
            res[i] = static_cast<int>((aa + ((bb % md) << 15) + ((cc % md) << 30)) % md);
        }
        return res;
    }
} // namespace fft

const int HALF = 499122177;
const int MOD = 1e9 + 7;
int add(int a, int b) {
    int res = a + b;
    if (res >= MOD) res -= MOD;
    return res;
}
int mul(int a, int b) { return (a * 1LL * b) % MOD; }
int ex(int n, int k) {
    int ans = 1;
    while (k) {
        if (k & 1) ans = mul(ans, n);
        n = mul(n, n);
        k >>= 1;
    }
    return ans;
}
int sub(int a, int b) { return add(a - b, MOD); }
int divide(int a, int b) { return mul(a, ex(b, MOD - 2)); }
int modinv(int x) { return divide(1, x); }

const int N = 15e6 + 9;
int fact[N];
void calc_fact();
int choose(int n, int r);

void solve() {
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    calc_fact();
    tt = 1, tc = 1; cin >> tt;
    while (tt--) solve(), tc++;
}

void calc_fact() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i < N; i++) {
        fact[i] = mul(i, fact[i - 1]);
    }
}

int choose(int n, int r) {
    if (n < r) return 0;
    if (r < 0 || n < 0) return 0; 
    return divide(fact[n], mul(fact[n - r], fact[r]));
}
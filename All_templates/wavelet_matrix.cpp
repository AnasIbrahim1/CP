#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

struct bit_vector{
    vector<unsigned long long> A;
    vector<int> S;
    bit_vector() {}
    bit_vector(vector<bool>& a) {
        int N = a.size(), M = (N + 64 - 1) >> 6;
        A = vector<unsigned long long>(M, 0);
        for (int i = 0; i < M; i++)
        for (int j = i << 6; j < min((i + 1) << 6, N); j++)
            if (a[j]) A[i] |= (unsigned long long) 1 << (j - (i << 6));

        S = vector<int>(M + 1, 0);
        for (int i = 0; i < M; i++) S[i + 1] = S[i] + __builtin_popcountll(A[i]);
    }
    int operator [](int k) { return A[k >> 6] >> (k & 63) & 1; }
    int rank0(int k) { return k - rank1(k); }
    int rank1(int k){
        if ((k & 63) == 0) return S[k >> 6];
        else return S[k >> 6] + __builtin_popcountll(A[k >> 6] << (64 - k + (k >> 6 << 6)));
    }
};

struct wavelet_matrix {
    int N, LOG;
    vector<bit_vector> D;
    vector<int> cnt, T;
    wavelet_matrix() {}
    wavelet_matrix(vector<int> A) : N((int)A.size()) {
        LOG = 1;
        for (int i = 0; i < N; i++) 
            if (A[i] > 0) LOG = max(LOG, 32 - __builtin_clz(A[i]));
        D.resize(LOG);
        cnt.resize(LOG, 0);
        for (int i = LOG - 1; i >= 0; i--){
            vector<bool> B(N);
            for (int j = 0; j < N; j++) 
                if ((A[j] >> i & 1) == 1) B[j] = true;
            D[LOG - 1 - i] = bit_vector(B);
            vector<int> A2;
            for (int j = 0; j < N; j++)
                if ((A[j] >> i & 1) == 0) 
                    A2.push_back(A[j]), cnt[LOG - 1 - i]++;
            for (int j = 0; j < N; j++)
                if ((A[j] >> i & 1) == 1)
                    A2.push_back(A[j]);
            swap(A, A2);
        }
        T = A;
    }
    int range_xor_max(int l, int r, int x){
        ++r;
        int ans = 0;
        for (int i = 0; i < LOG; i++) 
            if ((x >> (LOG - i - 1) & 1) == 0) {
                int cnt1 = D[i].rank1(r) - D[i].rank1(l);
                if (cnt1 > 0) {
                    ans += 1 << (LOG - 1 - i);
                    l = cnt[i] + D[i].rank1(l), r = cnt[i] + D[i].rank1(r);
                } else l = D[i].rank0(l), r = D[i].rank0(r);
            } else {
                int cnt0 = D[i].rank0(r) - D[i].rank0(l);
                if (cnt0 > 0){
                    ans += 1 << (LOG - 1 - i);
                    l = D[i].rank0(l), r = D[i].rank0(r);
                } else 
                    l = cnt[i] + D[i].rank1(l), r = cnt[i] + D[i].rank1(r);
            }
        return ans;
    }
    int range_xor_min(int l, int r, int x) {
        return INT_MAX ^ range_xor_max(l, r, INT_MAX ^ x);
    }
};

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}

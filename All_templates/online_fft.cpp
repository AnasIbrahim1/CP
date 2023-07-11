void solve() {
    int n;
    ll m;
    cin >> n >> m;
    int sz = 1;
    while (sz < (250001)) sz <<= 1;
    vector<ll> f(sz + 1);
    vector<ll> pref(sz + 1);
    for (int i = 1; i <= sz; i++) {
        f[i] = modpow(m, i);
        f[i] = sub(f[i], mul(pref[i >> 1], modpow(m, i)));
        pref[i] = divide(f[i], modpow(m, 2LL * i));
        pref[i] = add(pref[i - 1], pref[i]);
    }
    vector<ll> dp(sz);
    vector<ll> c(sz);
    dp[0] = 1;
    /*
    for (int k = 2; k <= (n >> 1); k++) {
        for (int i = 0; i <= k - 1; i++) dp[k] = add(dp[k], mul(dp[i], f[k - i]));
    }
    */
    // convolve b[i] = f[1 + i] and a[i] = dp[i], where dp[k] = c[k - 1]
    for (int i = 0; i < sz; i++) {
        int num = i + 1;
        num = (num & -num);
        // b[0] = f[1], b[1] = f[2], a[i]b[0] added to c[i] and a[i]b[1] is added to c[i + 1]
        c[i] = add(c[i], mul(dp[i], f[1]));
        if (i + 1 < sz) c[i + 1] = add(c[i + 1], mul(dp[i], f[2]));
        for (int pw = 2; pw <= num; pw <<= 1) {
            int l = pw, r = l + pw - 1;
            // convolve b[l] ... b[r], with
            int R = i, L = R - pw + 1;
            // dp[L] ... dp[R]
            vector<ll> a(pw), b(pw);
            for (int j = 0; j < pw; j++) {
                a[j] = dp[L + j];
                b[j] = (l + j + 1 <= sz ? f[l + j + 1] : 0);
            }
            auto res = convolution(a, b);
            for (int j = 0; j <= pw - 1 + pw - 1; j++) {
                int z = l + L + j;
                ll el = (j < (int)res.size() ? res[j] : 0LL);
                if (z < (int)c.size()) c[z] = add(c[z], el);
            }
        }
        if (i + 1 < sz) dp[i + 1] = c[i];
    }

    cout << dp[n >> 1] << "\n";
}
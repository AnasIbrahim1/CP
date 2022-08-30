#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, tc;

template <class T> struct assignment_prob {
    vector<int> assignment;
    vector<vector<T>> a;
    T INF;
    int n;

    assignment_prob(const vector<vector<T>>& given) { init(given); }
    void init(const vector<vector<T>>& given) { 
        a = given; 
        if (typeid(INF) == typeid(ll)) INF = (T)1e15;
        else INF = (T)1e9;
    }

    void assign() {
        n = a.size();
        int m = n * 2 + 2;
        vector<vector<int>> f(m, vector<int>(m));
        int s = m - 2, t = m - 1;
        T cost = 0;
        while (true) {
            vector<T> dist(m, INF);
            vector<int> p(m);
            vector<bool> inq(m, false);
            queue<int> q;
            dist[s] = 0;
            p[s] = -1;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                inq[v] = false;
                if (v == s) {
                    for (int i = 0; i < n; ++i) {
                        if (f[s][i] == 0) {
                            dist[i] = 0;
                            p[i] = s;
                            inq[i] = true;
                            q.push(i);
                        }
                    }
                } else {
                    if (v < n) {
                        for (int j = n; j < n + n; ++j) {
                            if (f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n]) {
                                dist[j] = dist[v] + a[v][j - n];
                                p[j] = v;
                                if (!inq[j]) {
                                    q.push(j);
                                    inq[j] = true;
                                }
                            }
                        }
                    } else {
                        for (int j = 0; j < n; ++j) {
                            if (f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n]) {
                                dist[j] = dist[v] - a[j][v - n];
                                p[j] = v;
                                if (!inq[j]) {
                                    q.push(j);
                                    inq[j] = true;
                                }
                            }
                        }
                    }
                }
            }

            T curcost = INF;
            for (int i = n; i < n + n; ++i) {
                if (f[i][t] == 0 && dist[i] < curcost) {
                    curcost = dist[i];
                    p[t] = i;
                }
            }
            if (curcost > INF/10)
                break;
            cost += curcost;
            for (int cur = t; cur != -1; cur = p[cur]) {
                int prev = p[cur];
                if (prev != -1)
                    f[cur][prev] = -(f[prev][cur] = 1);
            }
        }

        assignment.resize(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (f[i][j + n] == 1)
                    assignment[i] = j;
            }
        }
    }
    ll cost() {
        ll final_ans = 0;
        for (int i = 0; i < n; i++)
            final_ans += a[i][assignment[i]];
        return final_ans;
    }
};


void solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    tt = 1, tc = 1; //cin >> tt;
    while (tt--) solve(), tc++;
}
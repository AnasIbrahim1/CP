void euler(int u) {
    while (!g[u].empty()) {
        int v = *g[u].begin();
        g[u].erase(g[u].begin());
        g[v].erase(g[v].lower_bound(u));
        euler(v);
    }
    cout << u << " ";
}

// u u1 u2 u3 v1 v2 v3 v4 .. vk u3 ... uk u
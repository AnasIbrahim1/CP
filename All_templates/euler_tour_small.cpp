void euler(int u) {
    vis[u] = 1;
    while (!g[u].empty()) {
        int v = *g[u].begin();
        g[u].erase(g[u].begin());
        g[v].erase(g[v].lower_bound(u));
        euler(v);
        vis[v] = 1;
    }
    tour[tour_idx++] = u;
}
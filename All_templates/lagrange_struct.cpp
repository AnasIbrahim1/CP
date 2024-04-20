template <class T>
struct lagrange{
    vector<pair<T, T>> p; // assumes the first's are distinct
    lagrange(vector<pair<T, T>> points) : p(points) {} 
    T evaln(T x) { // assumes the step between points are constant and the points are increasing (in x-coordinates)
        for (auto& [v, y] : p) if (v == x) return y;
        T ans{};
        T prod_num = T(1), prod_denom = T(1);
        for (int i = 1; i < (int)p.size(); i++) {
            prod_num = prod_num * (x - p[i].first);
            prod_denom = prod_denom * (p[0].first - p[i].first);
        }
        ans = ans + (prod_num / prod_denom) * p[0].second;
        T step = p[1].first - p[0].first, r = p[0].first - p.back().first, l = step; 
        for (int i = 1; i < (int)p.size(); i++) {
            T v = p[i].first, y = p[i].second;
            prod_num = prod_num * (x - p[i - 1].first);
            prod_num = prod_num / (x - p[i].first);
 
            prod_denom = prod_denom * l;
            prod_denom = prod_denom / r;
 
            l = l + step;
            r = r + step;
 
            ans = ans + (prod_num / prod_denom) * y;
        }
        return ans;
    }
};

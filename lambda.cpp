//lambda cpp
vector<int> used(n + 1, 0), used2(n + 1, 0);
auto ds = [&](int x, auto&& ds) -> void {
    if(used[x] != inf) {
        used[x] = inf;
        x = a[x];
        ds(x, ds);
    }
};
auto dfs = [&](int x, auto&& dfs) -> void {
    if(used[x] == 2) {
        ds(x, ds);
    }
    if(used[x] == 1) {
        used[x]++;
        x = a[x];
        dfs(x, dfs);
        if(used[x] != inf) used[x] = 3;
    }
};

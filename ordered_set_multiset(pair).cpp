#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using namespace std;
typedef tree<pair<uint32_t, uint32_t>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // pair -> multiset, int -> set
// ordered_set s; // multiset: s.find_by_order(e - 1) -> first 
#pragma optimize ("g",on)
#pragma GCC optimize ("inline")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("03")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx2,mmx,fma,avx,tune=native")
#pragma comment(linker, "/stack:200000000")

//#define PI 3.1415926535897932384626433832795
//#define MOD 1000000007
//#define int long long
//#define ld double
#define endl "\n"
using ll = long long;
const int inf = 2e9;    

const ll MOD = 998244353;

using namespace std;

const int maxn = 100010;
vector<int> gr[maxn];
int tin[maxn], tout[maxn];
int t = 0;
vector<bool> used(maxn, 0);
void dfs (int v) {
    used[v] = true;
    tin[v] = t++;
    for (int u : gr[v])
        if(!used[u]) dfs(u);
    tout[v] = t;
}

int n, q; 
vector<vector<int>> qs(maxn, vector<int>());

map<pair<int, int>, int> ans;
map<int, int> help;
ordered_set s;
vector<bool> used2(maxn, 0);
void dfs2 (int v, int prev) {
    used2[v] = true;
    if(v != 1 || prev != 1) {
        int k1 = help[prev];
        int k2 = help[v];
        s.erase({k1, prev});
        s.erase({k2, v});
        k1 -= k2;
        k2 += k1;
        assert(k2 == n);
        help[prev] = k1;
        help[v] = k2;
        s.insert({k1, prev});
        s.insert({k2, v});
        for(auto e : qs[v]) {
            ans[{v, e}] = s.find_by_order(e - 1) -> first;
            //cout<< v << " " << e << "  =  " << s.find_by_order(e - 1)->first << endl;
        }
    }
    for (int u : gr[v])
        if(!used2[u]) dfs2(u, v);
    swap(v, prev);
    if(v != 1 || prev != 1) {
        int k1 = help[prev];
        int k2 = help[v];
        s.erase({k1, prev});
        s.erase({k2, v});
        k1 -= k2;
        k2 += k1;
        assert(k2 == n);
        help[prev] = k1;
        help[v] = k2;
        s.insert({k1, prev});
        s.insert({k2, v});
    }
}

void solve() {
    cin>> n >> q;
    
    for(int i = 1; i < n; i++) {
        int u, v; cin>> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    
    vector<pair<int, int>> qest;
    while(q--) {
        int v, k; cin>> v >> k;
        qs[v].push_back(k);
        qest.push_back({v, k});
    }
    
    dfs(1);
    for(int i = 1; i <= n; i++) {
        s.insert({tout[i] - tin[i], i});
        help[i] = tout[i] - tin[i];
        //cout<< tout[i] - tin[i] << " " << i << endl;
    }

    for(auto e : qs[1]) {
        ans[{1, e}] = s.find_by_order(e - 1) -> first;
        //cout<< e << " " << s.find_by_order(e - 1)->first << endl;
    }
    dfs2(1, 1);

    for(auto e : qest) {
        cout<< ans[{e.first, e.second}] << endl;
    }
    
}

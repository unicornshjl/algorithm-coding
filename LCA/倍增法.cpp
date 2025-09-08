#include<iostream>
#include<cmath>
#include<cstdio>
#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<utility>
#include<unordered_map>
#include<set>
#include<unordered_set>
using namespace std;
typedef long long ll;
constexpr int maxn = 1e6 + 10;
constexpr int maxm = 1e3 + 5;
constexpr int mod = 998244353;
constexpr int intinf = 2e9 + 10;
constexpr ll inf = 1e15 + 10;

int n, m, rt, cnt, to[maxn], nxt[maxn], head[maxn], dep[maxn], father[maxn], siz[maxn];
int tim, dfn[maxn], num[maxn], top[maxn], son[maxn];

void addedge(int u, int v) {
    to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

void init(){
    cin >> n >> m >> rt;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v); addedge(v, u);
    }
}


void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    father[u] = fa;
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}


void dfs2(int u, int fa) {
    dfn[u] = ++tim;
    top[u] = fa;
    num[tim] = u;
    if (son[u] == 0) return;
    dfs2(son[u], fa);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != father[u] && v != son[u])
            dfs2(v, v);
    }
}

int get_lca(int u,int v){
    while (top[u] != top[v]) {
        if (dep[top[u]] <= dep[top[v]])
            v = father[top[v]];
        else u = father[top[u]];
    }
    return dep[u] <= dep[v] ? u : v;
}

void solve() {
    dfs1(rt, 0);
    dfs2(rt, rt);
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << get_lca(x, y) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    init();
    solve();
    return 0;
}

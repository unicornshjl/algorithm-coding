利用重链剖分代替 倍增法求lca 以及 倍增法向上跳k步
当然后一个问题尅应用长链剖分更快地解决 但本题数据范围 1e6 故 O(N log N) 的算法可以通过
但是 倍增法由于常数过大无法通过 于是采用树剖

#include<algorithm>
#include<bitset>
#include<climits>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//constexpr int mod = 1e9 + 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9 + 1e8;

#define lson(x) x << 1
#define rson(x) x << 1 | 1

ll read() {
    ll s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c >'9') {
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        s = s * 10 + c - 48;
        c = getchar();
    }
    return s * w;
}

ll gcd(ll x, ll y) {
    return(y == 0 ? x : gcd(y, x % y));
}

ll ksm(ll a, ll b) {
    if (b < 0) return 0;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a;// % mod;
        a = a * a;// % mod;
        b >>= 1;
    }
    return res;
}

int lowbit(int x) {
    return x & (-x);
}

constexpr int maxn = 1e6 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, k, dep[maxn], x, father[maxn], son[maxn], siz[maxn], dfn[maxn], top[maxn], tim, seg[maxn];

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    father[u] = fa;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int head) {
    top[u] = head; dfn[u] = ++tim; seg[tim] = u;
    if (son[u] == 0) return;
    dfs2(son[u], head);
    for (auto v : edge[u]) {
        if (v == son[u] || v == father[u]) continue;
        dfs2(v, v);
    }
}

int get_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = father[top[u]];
    }
    return(dfn[u] < dfn[v] ? u : v);
}

int move(int x, int step) {
    while (step > 0) {
        int cur = dfn[x] - dfn[top[x]];
        if (step <= cur) {
            return seg[dfn[x] - step];
        }
        x = father[top[x]];
        step -= cur + 1;
    }
    if (step == 0) return x;
}

void solve() {
    n = read(), x = read(), k = read();
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    while (k--) {
        int d = read(), t = read();
        int lca = get_lca(x, d);
        int dis = dep[x] + dep[d] - dep[lca] * 2;
        if (t >= dis) {
            x = d;
        }
        else {
            int d1 = dep[x] - dep[lca];
            if (t <= d1) {
                x = move(x, t);
            }
            else {
                int d2 = dis - t;
                d = move(d, d2);
                x = d;
            }
        }
        printf("%d ", x);
    }
}

signed main() { 
    //ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

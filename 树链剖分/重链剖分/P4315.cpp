本题仍然是边权转点权的模板题 
但是需要注意本题的线段树有 区间修改 和 区间加 两种操作
那么显然区间修改为某一个值之后原先的 区间加 操作的值作废
而当已经进行了 区间修改 的操作之后 区间加 的懒标记的值应该直接加在修改的标记上而非加的标记上
本题的主要难点还是在两种区间操作的线段树上


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
constexpr int intinf = 1e9;

#define lson(x) x << 1
#define rson(x) x << 1 | 1

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

constexpr int maxn = 8e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, u[maxn], v[maxn], w[maxn], dep[maxn], father[maxn], seg[maxn], dfn[maxn], tim, son[maxn], siz[maxn], top[maxn];
int p[maxn], a[maxn], tr[maxn];
bool vis[maxn];

struct node {
    int ad, cv;
} lazy[maxn];
vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    father[u] = fa;
    siz[u] = 1;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int head) {
    top[u] = head;
    dfn[u] = ++tim; seg[tim] = u;
    if (son[u] == 0) return;
    dfs2(son[u], head);
    for (auto v : edge[u]) {
        if (v == father[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void up(int x) {
    tr[x] = max(tr[lson(x)], tr[rson(x)]);
}

void down(int x) {
    if (vis[x]) {
        int p = lazy[x].cv;
        lazy[x].ad = 0;
        lazy[x].cv = 0;
        lazy[lson(x)].cv = p;
        lazy[rson(x)].cv = p;
        lazy[lson(x)].ad = 0;
        lazy[rson(x)].ad = 0;
        tr[lson(x)] = tr[rson(x)] = p;
        vis[x] = 0; 
        vis[lson(x)] = vis[rson(x)] = 1;
    }
    if (lazy[x].ad) {
        int p = lazy[x].ad;
        if (vis[lson(x)]) lazy[lson(x)].cv += p;
        else lazy[lson(x)].ad += p;
        if (vis[rson(x)]) lazy[rson(x)].cv += p;
        else lazy[rson(x)].ad += p;
        tr[lson(x)] += p;
        tr[rson(x)] += p;
        lazy[x].ad = 0;
    }
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x] = a[seg[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int ql, int qr, int x, int l, int r, int w){
    if (ql <= l && r <= qr) {
        tr[x] = w;
        lazy[x].cv = w;
        lazy[x].ad = 0;
        vis[x] = 1;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, w);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, w);
    up(x);
}

void addval(int ql, int qr, int x, int l, int r, int w) {
    if (ql <= l && r <= qr) {
        if (vis[x]) {
            tr[x] += w;
            lazy[x].cv += w;
        }
        else {
            tr[x] += w;
            lazy[x].ad += w;
        }
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) addval(ql, qr, lson(x), l, mid, w);
    if (qr > mid) addval(ql, qr, rson(x), mid + 1, r, w);
    up(x);
}

int query(int ql, int qr, int x,int l, int r) {
    if (ql <= l && r <= qr) return tr[x];
    down(x);
    int res = 0;
    int mid = (l + r) / 2;
    if (ql <= mid) res = max(res, query(ql, qr, lson(x), l, mid));
    if (qr > mid) res = max(res, query(ql, qr, rson(x), mid + 1, r));
    return res;
}

int queryPath(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])  swap(u, v);
        res = max(res, query(dfn[top[u]], dfn[u], 1, 1, n));
        u = father[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    u = son[u];
    if (u && dfn[u] <= dfn[v]) res = max(res, query(dfn[u], dfn[v], 1, 1, n));
    return res;
}

void updatePath(int u, int v,int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n, w);
        u = father[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    u = son[u];
    if (u && dfn[u] <= dfn[v]) update(dfn[u], dfn[v], 1, 1, n, w);
}

void addPath(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        addval(dfn[top[u]], dfn[u], 1, 1, n, w);
        u = father[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    u = son[u];
    if (u && dfn[u] <= dfn[v]) addval(dfn[u], dfn[v], 1, 1, n, w);
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u[i] >> v[i] >> w[i];
        add(u[i], v[i]); add(v[i], u[i]);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i < n; i++) {
        p[i] = (dep[u[i]] > dep[v[i]] ? u[i] : v[i]);
        a[p[i]] = w[i];
    }
    build(1, 1, n);
    string op;
    cin >> op;
    while (op != "Stop") {
        int x, y, z;
        if (op == "Max") {
            cin >> x >> y;
            cout << queryPath(x, y) << "\n";
        }
        if (op == "Cover") {
            cin >> x >> y >> z;
            updatePath(x, y, z);
        }
        if (op == "Change") {
            cin >> x >> z;
            update(dfn[p[x]], dfn[p[x]], 1, 1, n, z);
        }
        if (op == "Add") {
            cin >> x >> y >> z;
            addPath(x, y, z);
        }
        cin >> op;
    }
}

signed main() { 
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

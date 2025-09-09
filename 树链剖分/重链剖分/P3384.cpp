本题为树链剖分模板题 构建的线段树为 维护区间加和区间求和 的线段树
利用树剖之后 dfn 序的特点 将树上问题转化为普通线段树的区间问题

关键是路径如何处理 因为子树实际上只不需要树剖 用普通的 dfs 序也能够解决

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

constexpr int maxn = 4e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, rt, mod, a[maxn], siz[maxn], dep[maxn], son[maxn], dfn[maxn], seg[maxn], father[maxn], tim, top[maxn];
ll tr[maxn], lazy[maxn];
vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    father[u] = fa;
    dep[u] = dep[fa] + 1;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int head) {
    dfn[u] = ++tim; seg[tim] = u;
    top[u] = head;
    if (son[u] == 0) return;
    dfs2(son[u], head);
    for (auto v : edge[u]) {
        if (v == father[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void up(int x) {
    tr[x] = (tr[lson(x)] + tr[rson(x)]) % mod;
}

void down(int x,int l,int r) {
    if (lazy[x] == 0) return;
    int mid = (l + r) / 2;
    tr[lson(x)] = (tr[lson(x)] + lazy[x] * (ll)(mid - l + 1) % mod) % mod;
    tr[rson(x)] = (tr[rson(x)] + lazy[x] * (ll)(r - mid) % mod) % mod;
    lazy[lson(x)] = (lazy[lson(x)] + lazy[x]) % mod;
    lazy[rson(x)] = (lazy[rson(x)] + lazy[x]) % mod;
    lazy[x] = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x] = a[seg[l]] % mod;
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int ql, int qr, int x, int l, int r, ll v) {
    if (ql <= l && r <= qr) {
        tr[x] = (tr[x] + v * (ll)(r - l + 1) % mod) % mod;
        lazy[x] = (lazy[x] + v) % mod;
        return;
    }
    down(x, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, v);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, v);
    up(x);
}

ll query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) {
        return tr[x] % mod;
    }
    ll res = 0;
    down(x, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) res = (res + query(ql, qr, lson(x), l, mid)) % mod;
    if (qr > mid) res = (res + query(ql, qr, rson(x), mid + 1, r)) % mod;
    return res;
}

void addPath(int u, int v, ll w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n, w % mod);
        u = father[top[u]];
    }
    update(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n, w % mod);
}

ll queryPath(int u, int v) {
    ll sum = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        sum = (sum + query(dfn[top[u]], dfn[u], 1, 1, n)) % mod;
        u = father[top[u]];
    }
    sum = (sum + query(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n)) % mod;
    return sum;
}

void addSub(int u, int w) {
    update(dfn[u], dfn[u] + siz[u] - 1, 1, 1, n, w % mod);
}

ll querySub(int u){
    return query(dfn[u], dfn[u] + siz[u] - 1, 1, 1, n);
}

void solve() {
    cin >> n >> m >> rt >> mod;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs1(rt, 0);
    dfs2(rt, rt);
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int op, x, y, z;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            addPath(x, y, z);
        }
        if (op == 2) {
            cin >> x >> y;
            cout << queryPath(x, y) << "\n";
        }
        if (op == 3) {
            cin >> x >> z;
            addSub(x, z);
        }
        if (op == 4) {
            cin >> x;
            cout << querySub(x) << "\n";
        }
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

线段树更复杂了 所以相应的 up , query 和 树链合并的代码显得复杂
首先由于要获得最大利润 那么我们一定要维护区间最大值和区间最小值的信息
然后我们还需要维护的是 线段树上从左到右的最大利润 和 线段树上从右到左的最大利润
那么这实际上就对应了 树上 dfn 序小的到 dfn 序大的最大利润 和 树上 dfn 大的到书上dfn序小的最大利润
为什么我们需要从左到右和从右到左都维护呢 因为题目中路径是有方向的 : from u to v
那么这个过程实际上可以拆分成 u 到 lca lca 到 v 那么显然  lca 的 dfn 序不会大于 u 和 v 的 dfn 序
这也就意味着 从u 到 lca的过程中我们是从 dfn 序大的到 dfn 序小的 而从 lca to v 的过程中我们是从 dfn 序小的到 dfn 序大的
对应着我们线段树上从左到右和从右到左维护的两个信息 lprofit 和 rprofit
需要注意的是当 u 和 v 处于同一重链的时候 需要去判断谁的 dfn 序大 谁的 dfn 序小 从而判断出应该使用 lprofit 还是 rprofit

在合并的时候 最大值和最小值显然是可以直接向上合并的
而 lprofit 和 rprofit 不仅要从 左右儿子中选出较大者 还需要根据公式额外计算
例如 lprofit = max(Llporfit, Llprofit, R_max - Lmin);
类似的 , 在合并答案的时候都应采用这个逻辑


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

int n, a[maxn], dep[maxn], son[maxn], father[maxn], siz[maxn], dfn[maxn], seg[maxn], top[maxn], tim, lazy[maxn];

vector<int> edge[maxn];

struct node {
    int MIN, MAX, lpro, rpro;
} tr[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    father[u] = fa;
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
        if (v == son[u] || v == father[u]) continue;
        dfs2(v, v);
    }
}

void up(int x) {
    tr[x].MIN = min(tr[lson(x)].MIN, tr[rson(x)].MIN);
    tr[x].MAX = max(tr[lson(x)].MAX, tr[rson(x)].MAX);
    tr[x].lpro = max({ tr[lson(x)].lpro, tr[rson(x)].lpro,tr[rson(x)].MAX - tr[lson(x)].MIN });
    tr[x].rpro = max({ tr[lson(x)].rpro, tr[rson(x)].rpro,tr[lson(x)].MAX - tr[rson(x)].MIN });
}

void down(int x) {
    if (lazy[x]) {
        int cur = lazy[x];
        tr[lson(x)].MIN += cur;
        tr[lson(x)].MAX += cur;
        tr[rson(x)].MIN += cur;
        tr[rson(x)].MAX += cur;
        lazy[lson(x)] += cur;
        lazy[rson(x)] += cur;
    }
    lazy[x] = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x].MIN = tr[x].MAX = a[seg[l]];
        tr[x].lpro = tr[x].rpro = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int ql, int qr, int x, int l, int r, int w) {
    if (ql <= l && r <= qr) {
        tr[x].MIN += w;
        tr[x].MAX += w;
        lazy[x] += w;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, w);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, w);
    up(x);
}

void addPath(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n, w);
        u = father[top[u]];
    }
    update(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n, w);
}

node query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return tr[x];
    int Lmin = intinf, Rmin = intinf, Lmax = -intinf, Rmax = -intinf, Lpro = 0, Rpro = 0;
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        node T = query(ql, qr, lson(x), l, mid);
        Lmin = min(Lmin, T.MIN); 
        Lmax = max(Lmax, T.MAX);
        Lpro = max(Lpro, T.lpro); 
        Rpro = max(Rpro, T.rpro);
    }
    if (qr > mid) {
        node T = query(ql, qr, rson(x), mid + 1, r);
        Rmin = min(Rmin, T.MIN); 
        Rmax = max(Rmax, T.MAX);
        Lpro = max(Lpro, T.lpro); 
        Rpro = max(Rpro, T.rpro);
    }
    return { min(Lmin,Rmin),max(Lmax,Rmax),max(Lpro,Rmax - Lmin),max(Rpro,Lmax - Rmin) };
}

int queryPath(int u, int v) {
    node L = { intinf, -intinf,0,0 }, R = L;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) {
            node T = query(dfn[top[u]], dfn[u], 1, 1, n);
            L.rpro = max({ L.rpro, T.MAX - L.MIN ,T.rpro});
            L.MIN = min(L.MIN, T.MIN);
            L.MAX = max(L.MAX, T.MAX);
            u = father[top[u]];
        }
        else {
            node T = query(dfn[top[v]], dfn[v], 1, 1, n);
            v = father[top[v]];
            R.lpro = max({ R.lpro, R.MAX - T.MIN ,T.lpro });
            R.MIN = min(R.MIN, T.MIN);
            R.MAX = max(R.MAX, T.MAX);
        }
    }
    if (dfn[u] < dfn[v]) {
        node T = query(dfn[u], dfn[v], 1, 1, n);
        R.lpro = max({ R.lpro, R.MAX - T.MIN ,T.lpro });
        R.MIN = min(R.MIN, T.MIN);
        R.MAX = max(R.MAX, T.MAX);

    }
    else {
        node T = query(dfn[v], dfn[u], 1, 1, n);
        L.rpro = max({ L.rpro, T.MAX - L.MIN ,T.rpro });
        L.MIN = min(L.MIN, T.MIN);
        L.MAX = max(L.MAX, T.MAX);
    }
    return max({ L.rpro,R.lpro, R.MAX - L.MIN });
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    int Q;
    cin >> Q;
    while (Q--) {
        int u, v, w;
        cin >> u >> v >> w;
        cout << queryPath(u, v) << "\n";
        addPath(u, v, w);
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

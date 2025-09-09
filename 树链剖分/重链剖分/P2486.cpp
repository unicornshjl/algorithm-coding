从本题开始对线段树所维护的信息有了进一步的要求 主要是在 up , query 和 树链合并 的过程中有了不同，而这三者实际上逻辑是一致的
显然 , 本题中我们线段树需要维护的信息有颜色段的数量 sum 区间最左端颜色 lc 和 区间最右端颜色 rc
有了这三个信息之后 考虑 up 的过程
假设我们已经知道了左儿子 lson 和右儿子 rson 的相关信息 那么对于该节点 x 的信息 , 有
左端颜色就是 lson 的左端颜色 右端颜色就是 rson 的右端颜色 而 sum 并非简单的左右儿子相加 而需要另外判断 lson 的 rc 和 rson 的 lc 是否相同 , 倘若相同则证明在拼接过程中我们多算了,应该将其减去

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

int n, m, a[maxn], dep[maxn], siz[maxn], father[maxn], dfn[maxn], seg[maxn], son[maxn], tim, top[maxn], lazy[maxn];

vector<int> edge[maxn];

struct node {
    int sum, lc, rc;
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
        if (v == father[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void up(int x) {
    tr[x].sum = tr[lson(x)].sum + tr[rson(x)].sum;
    if (tr[lson(x)].rc == tr[rson(x)].lc) 
        tr[x].sum--;
    tr[x].lc = tr[lson(x)].lc;
    tr[x].rc = tr[rson(x)].rc;
}

void down(int x) {
    if (lazy[x]) {
        lazy[lson(x)] = lazy[x];
        lazy[rson(x)] = lazy[x];
        tr[lson(x)].sum = 1;
        tr[rson(x)].sum = 1; 
        tr[lson(x)].lc = tr[lson(x)].rc = lazy[x];
        tr[rson(x)].lc = tr[rson(x)].rc = lazy[x];
    }
    lazy[x] = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x].lc = tr[x].rc = a[seg[l]];
        tr[x].sum = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int ql, int qr, int x, int l, int r, int w) {
    if (ql <= l && r <= qr) {
        tr[x].sum = 1;
        tr[x].lc = tr[x].rc = w;
        lazy[x] = w;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, w);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, w);
    up(x);
}

int querycol(int qid, int x, int l, int r) {
    if (l == r && l == qid)
        return tr[x].lc;
    down(x);
    int mid = (l + r) / 2;
    if (qid <= mid) return querycol(qid, lson(x), l, mid);
    else return querycol(qid, rson(x), mid + 1, r);
}

int query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) 
        return tr[x].sum;
    down(x);
    int mid = (l + r) / 2;
    if (qr <= mid) return query(ql, qr, lson(x), l, mid);
    else if (ql > mid) return query(ql, qr, rson(x), mid + 1, r);
    else {
        int ans = query(ql, qr, lson(x), l, mid) + query(ql, qr, rson(x), mid + 1, r);
        //if (querycol(mid, 1, 1, n) == querycol(mid + 1, 1, 1, n)) ans--;
        if (tr[rson(x)].lc == tr[lson(x)].rc) ans--;
        return ans;
    }
}

int queryPath(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])  swap(u, v);
        ans += query(dfn[top[u]], dfn[u], 1, 1, n);
        if (querycol(dfn[top[u]], 1, 1, n) == querycol(dfn[father[top[u]]], 1, 1, n)) ans--;
        u = father[top[u]];
    }
    ans += query(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n);
    return ans;
}


void updatePath(int u, int v,int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n, w);
        u = father[top[u]];
    }
    update(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n, w);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (m--) {
        char op; int u, v, w;
        cin >> op;
        if (op == 'Q') {
            cin >> u >> v;
            cout << queryPath(u, v) << "\n";
        }
        else {
            cin >> u >> v >> w;
            updatePath(u, v, w);
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

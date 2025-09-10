本题也是边权转化为点权的题目 按照trick处理即可
但是要注意，本题中涉及单点修改和区间取相反数两种操作
单点修改不需要懒标记而区间修改需要 那么在单点修改的过程中仍然要将懒标记下放 否则可能该点上对应的值已经取了相反数但是单点修改时还按照原值在计算
由于只有一个区间修改 本题仍然不涉及多种懒标记的顺序以及覆盖问题

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

int n, u[maxn], v[maxn], w[maxn], father[maxn], siz[maxn], dep[maxn], son[maxn], top[maxn], seg[maxn], dfn[maxn];
int tim, a[maxn], p[maxn];
bool lazy[maxn]; 

struct node {
    int MAX, MIN, sum;
} tr[maxn];

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    father[u] = fa;
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v])
            son[u] = v;
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
    tr[x].MIN = min(tr[lson(x)].MIN, tr[rson(x)].MIN);
    tr[x].MAX = max(tr[lson(x)].MAX, tr[rson(x)].MAX);
    tr[x].sum = tr[lson(x)].sum + tr[rson(x)].sum;
}

void down(int x) {
    if (lazy[x]) {
        tr[lson(x)].sum *= -1;
        tr[rson(x)].sum *= -1;
        int p = tr[lson(x)].MAX, q = tr[rson(x)].MAX;
        tr[lson(x)].MAX = -tr[lson(x)].MIN;
        tr[lson(x)].MIN = -p;
        tr[rson(x)].MAX = -tr[rson(x)].MIN;
        tr[rson(x)].MIN = -q;
        lazy[lson(x)] ^= 1;
        lazy[rson(x)] ^= 1;
    }
    lazy[x] = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        if (seg[l] != 1)
            tr[x].MIN = tr[x].MAX = tr[x].sum = a[seg[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int qid, int x, int l, int r, int v) {
    if (qid == l && qid == r) {
        tr[x].MAX = tr[x].sum = tr[x].MIN = v;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (qid <= mid) update(qid, lson(x), l, mid, v);
    if (qid > mid) update(qid, rson(x), mid + 1, r, v);
    up(x);
}

void change(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) {
        tr[x].sum *= -1;tr[x].MAX *= -1; tr[x].MIN *= -1;
        swap(tr[x].MAX, tr[x].MIN);
        lazy[x] ^= 1;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) change(ql, qr, lson(x), l, mid);
    if (qr > mid) change(ql, qr, rson(x), mid + 1, r);
    up(x);
}

node query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return tr[x];
    down(x);
    node res = { -intinf,intinf,0 };
    int mid = (l + r) / 2;
    if (ql <= mid) {
        node T = query(ql, qr, lson(x), l, mid);
        res.MIN = min(res.MIN, T.MIN);
        res.MAX = max(res.MAX, T.MAX);
        res.sum += T.sum;
    }
    if (qr > mid) {
        node T = query(ql, qr, rson(x), mid + 1, r);
        res.MIN = min(res.MIN, T.MIN);
        res.MAX = max(res.MAX, T.MAX);
        res.sum += T.sum;
    }
    return res;
}

node queryPath(int u, int v) {
    node res = { -intinf,intinf,0 };
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        node T = query(dfn[top[u]], dfn[u], 1, 1, n);
        res.MIN = min(res.MIN, T.MIN);
        res.MAX = max(res.MAX, T.MAX);
        res.sum += T.sum;
        u = father[top[u]];
    }
    if (dfn[u] < dfn[v]) {
        u = son[u];
        if (dfn[u] <= dfn[v]) {
            node T = query(dfn[u], dfn[v], 1, 1, n);
            res.MIN = min(res.MIN, T.MIN);
            res.MAX = max(res.MAX, T.MAX);
            res.sum += T.sum;
        }
    }
    else{
        v = son[v];
        if (dfn[v] <= dfn[u]) {
            node T = query(dfn[v], dfn[u], 1, 1, n);
            res.MIN = min(res.MIN, T.MIN);
            res.MAX = max(res.MAX, T.MAX);
            res.sum += T.sum;
        }
    }
    return res;
}

void changePath(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        change(dfn[top[u]], dfn[u], 1, 1, n);
        u = father[top[u]];
    }
    if (dfn[u] < dfn[v]) {
        u = son[u];
        if (dfn[u] <= dfn[v])
            change(dfn[u], dfn[v], 1, 1, n);
    }
    else {
        v = son[v];
        if (dfn[v] <= dfn[u])
            change(dfn[v], dfn[u], 1, 1, n);
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u[i] >> v[i] >> w[i];
        u[i]++; v[i]++;
        add(u[i], v[i]); add(v[i], u[i]);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i < n; i++) {
        p[i] = (dep[v[i]] > dep[u[i]] ? v[i] : u[i]);
        a[p[i]] = w[i];
    }
    for (int i = 1; i <= 4 * n; i++)
        tr[i] = { -intinf,intinf,0 };
    build(1, 1, n);
    int Q; cin >> Q;
    while (Q--) {
        string op; int x, y;
        cin >> op >> x >> y;
        x++; y++;
        if (op == "SUM") cout << queryPath(x, y).sum << "\n";
        if (op == "MAX") cout << queryPath(x, y).MAX << "\n";
        if (op == "MIN") cout << queryPath(x, y).MIN << "\n";
        if (op == "N") changePath(x, y);
        if (op == "C") {
            x--; y--;
            update(dfn[p[x]], 1, 1, n, y);
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

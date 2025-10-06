/*
    将线段树的功能改为了 区间修改、查询区间和以及查询区间最大值 本质依旧是将树转化为普通线段树的问题
*/


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

int n, dep[maxn], siz[maxn], father[maxn], son[maxn], dfn[maxn], seg[maxn], tim, a[maxn], top[maxn];
vector<int> edge[maxn];

struct node {
    int MAX; ll sum;
} tr[maxn];

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
    tr[x].MAX = max(tr[lson(x)].MAX, tr[rson(x)].MAX);
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x].sum = a[seg[l]];
        tr[x].MAX = a[seg[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int qid, int x, int l, int r, int v) {
    if (qid == l && qid == r) {
        tr[x].sum = v;
        tr[x].MAX = v;
        return;
    }
    int mid = (l + r) / 2;
    if (qid <= mid) update(qid, lson(x), l, mid, v);
    if (qid > mid) update(qid, rson(x), mid + 1, r, v);
    up(x);
}

int querymax(int ql, int qr, int x, int l, int r) {
    int res = -intinf;
    if (ql <= l && r <= qr) return tr[x].MAX;
    int mid = (l + r) / 2;
    if (ql <= mid) res = max(res, querymax(ql, qr, lson(x), l, mid));
    if (qr > mid) res = max(res, querymax(ql, qr, rson(x), mid + 1, r));
    return res;
}

ll querysum(int ql, int qr, int x, int l, int r) {
    ll res = 0;
    if (ql <= l && r <= qr) return tr[x].sum;
    int mid = (l + r) / 2;
    if (ql <= mid) res += querysum(ql, qr, lson(x), l, mid);
    if (qr > mid) res += querysum(ql, qr, rson(x), mid + 1, r);
    return res;
}

int queryPathMAX(int u,int v) {
    int ans = -intinf;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans = max(ans, querymax(dfn[top[u]], dfn[u], 1, 1, n));
        u = father[top[u]];
    }
    ans = max(ans, querymax(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n));
    return ans;
}


ll queryPathSUM(int u, int v) {
    ll ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += querysum(dfn[top[u]], dfn[u], 1, 1, n);
        u = father[top[u]];
    }
    ans += querysum(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n);
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    int Q;
    cin >> Q;
    while (Q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;
        if (op == "QMAX") 
            cout << queryPathMAX(u, v) << "\n";
        if (op == "QSUM")
            cout << queryPathSUM(u, v) << "\n";
        if (op == "CHANGE")
            update(dfn[u], 1, 1, n, v);
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

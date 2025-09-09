本题要先将题目略微转化 然后转化为 路径修改 和 子树修改问题，由于问的是全局该变量，所以只需要关注线段树上1号节点值的变化即可


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

int n, dep[maxn], son[maxn], dfn[maxn], siz[maxn], father[maxn], top[maxn], tim;
int tr[maxn], lazy[maxn];
bool vis[maxn];

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    father[u] = fa;
    siz[u] = 1;
    for (auto v : edge[u]) {
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void dfs2(int u,int head){
    top[u] = head;
    dfn[u] = ++tim;
    if (son[u] == 0) return;
    dfs2(son[u], head);
    for (auto v : edge[u]) {
        if (v == father[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void down(int x,int l,int r) {
    if (vis[x]) {
        int mid = (l + r) / 2;
        lazy[lson(x)] = lazy[x];
        lazy[rson(x)] = lazy[x];
        tr[lson(x)] = lazy[x] * (mid - l + 1);
        tr[rson(x)] = lazy[x] * (r - mid);
        vis[lson(x)] = 1;
        vis[rson(x)] = 1;
    }
    vis[x] = 0;
}

void up(int x) {
    tr[x] = tr[lson(x)] + tr[rson(x)];
}

void update(int ql, int qr, int x, int l, int r, int v) {
    if (ql <= l && r <= qr) {
        tr[x] = v * (r - l + 1);
        lazy[x] = v;
        vis[x] = 1;
        return;
    }
    down(x , l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, v);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, v);
    up(x);
}

int updatePath(int u, int v) {
    int sum1 = tr[1];
    while (top[u] != top[v]) {
        update(dfn[top[u]], dfn[u], 1, 1, n, 1);
        u = father[top[u]];
    }
    update(1, dfn[u], 1, 1, n, 1);
    return tr[1] - sum1;
}

int updateSub(int x) {
    int sum1 = tr[1];
    update(dfn[x], dfn[x] + siz[x] - 1, 1, 1, n, 0);
    return sum1 - tr[1];
}

void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        u++;
        add(u, i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int Q;
    cin >> Q;
    while (Q--) {
        string op; int x;
        cin >> op >> x;
        x++;
        if (op[0] == 'i') {
            cout << updatePath(x, 1) << "\n";
        }
        else {
            cout << updateSub(x) << "\n";
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

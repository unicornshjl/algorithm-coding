/*
  链接 : https://www.luogu.com.cn/problem/P4074
  树上带修莫队 实际上就是树上莫队+带修莫队
  还是"出现次数"类型的题目 根据题意模拟即可
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
constexpr int mod = 998244353;
constexpr ll inf = 1e18;

constexpr int maxn = 2e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, f[maxn][N], dep[maxn], seg[maxn], st[maxn], ed[maxn], tim, g, C[maxn];
ll v[maxn], w[maxn], res[maxn], ans, h[maxn];
bool vis[maxn];

vector<int> edge[maxn];


struct node{
    int l, r, bl, br, id, t, lca;
} q[maxn];

struct Node {
    int p, x;
} Q[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs(int u, int fa) {
    st[u] = ++tim; seg[tim] = u;
    f[u][0] = fa;
    for (int i = 1; i < N; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    dep[u] = dep[fa] + 1;
    for (auto v : edge[u])
        if (v != fa) dfs(v, u);
    ed[u] = ++tim; seg[tim] = u;
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    for (int i = N - 1; i >= 0; i--)
        if ((k >> i) & 1) u = f[u][i];
    if (u == v) return u;
    for (int i = N - 1; i >= 0; i--)
        if (f[v][i] != f[u][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

bool cmp(node c1, node c2) {
    if (c1.bl == c2.bl) {
        if (c1.br == c2.br) return c1.t < c2.t;
        return c1.br < c2.br;
    }
    return c1.bl < c2.bl;
}

void change(int x) {
    int c = C[x];
    if (vis[x]) {
        ans -= v[c] * w[h[c]];
        h[c]--;
    }
    else {
        h[c]++;
        ans += v[c] * w[h[c]];
    }
    vis[x] ^= 1;
}

void update(int T) {
    int p = Q[T].p, x = Q[T].x;
    if (vis[p]) {
        change(p);
        swap(Q[T].x, C[p]);
        change(p);
    }
    else {
        swap(Q[T].x, C[p]);
    }
}

void solve() {
    cin >> n >> g >> m;
    for (int i = 1; i <= g; i++)
        cin >> v[i];
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    for (int i = 1; i <= n; i++)
        cin >> C[i];
    dfs(1, 0); 
    int num = 0, cnt = 0;
    int B = pow(tim, 2.0 / 3);
    for (int i = 1; i <= m; i++){
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            cin >> u >> v;
            int lca = get_lca(u, v);
            cnt++;
            q[cnt].id = cnt;
            if (dep[u] > dep[v]) swap(u, v);
            if (u == lca) {
                q[cnt].l = st[u]; q[cnt].r = st[v];
                q[cnt].bl = (st[u] - 1) / B + 1;
                q[cnt].br = (st[v] - 1) / B + 1;
                q[cnt].t = num;
                q[cnt].lca = 0;
            }
            else {
                if (ed[u] > st[v]) swap(u, v);
                q[cnt].l = ed[u]; q[cnt].r = st[v];
                q[cnt].bl = (ed[u] - 1) / B + 1;
                q[cnt].br = (st[v] - 1) / B + 1;
                q[cnt].t = num;
                q[cnt].lca = lca;
            }
        }
        else {
            int x, y;
            cin >> x >> y;
            num++;
            Q[num].p = x; Q[num].x = y;
        }
    }
    sort(q + 1, q + cnt + 1, cmp);
    int l = 1, r = 0, T = 0;
    for (int i = 1; i <= cnt; i++) {
        while (l > q[i].l) change(seg[--l]);
        while (r < q[i].r) change(seg[++r]);
        while (l < q[i].l) change(seg[l++]);
        while (r > q[i].r) change(seg[r--]);
        if (q[i].lca != 0) change(q[i].lca);
        while (T < q[i].t) update(++T);
        while (T > q[i].t) update(T--);
        res[q[i].id] = ans;
        if (q[i].lca != 0) change(q[i].lca);
    }
    for (int i = 1; i <= cnt; i++)
        cout << res[i] << '\n';
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

编号最大值为代价即为瓶颈路。考虑 Kruskal 重构树。

这里边权即为编号，我们需要按照边权从小到大排序构建出 Kruskal 重构树。

然后考虑两人恰好访问 $z$ 个顶点应该如何处理。

我们可以考虑二分答案。假设当前答案为 $mid$，那么我们去统计两人能访问的总结点。若总结点个数 $\ge z$ 表明当前的 $mid$ 是合法的，继续向小答案二分。于是问题就转换为了如何统计 $\le mid$ 的总节点数。

那么我们可以先把两个节点分开来考虑。先考虑一个节点的情况。

一个点的情况就比较简单了，只能让它不断地上跳，跳到某个节点 $u$ 使得 $u$ 的点权 $\le mid$ 但 $u$ 的父亲的点权 $\gt mid$ 。那么 $u$ 的子树内含有的原树节点(即重构树中的叶子结点)个数(记作 $siz[u]$)即为一个人能跳到的节点数。

那么两个点的情况其实就是两次一个点的状态的合并。此时有两种情况，如下图所示。

- 两个节点分别为 $2$ 和 $4，mid = 2$，那么子树为两个红色部分的合并。
- 两个节点分别为 $1$ 和 $3，mid = 3$，那么子树为绿色部分。

也就意味着，当两个点 $u$ 和 $v$ 不断上跳之后 存在两种可能性。

- $u = v$：它们最终跳到了同一个节点，故两个节点能走的总结点即为 $siz[u]$。
- $u \neq v$：它们没有跳到一起，故总结点为 $siz[u] + siz[v]$。

![](https://raw.githubusercontent.com/unicornshjl/MyPic/img/test/61051a0f09021d3f8af61e8580e548a4.jpg)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
#include<cstring>
#include<string>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<climits>
#include<bitset>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int mod = 1e9 + 7;
constexpr ll inf = 2e14;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
 
int n, m, cnt, f[maxn], siz[maxn], fa[maxn][N], val[maxn];

pair<int, int> E[maxn];
vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

int find(int x) {
    return (x == f[x] ? x : f[x] = find(f[x]));
}

void dfs(int u, int father) {
    if (u >= 1 && u <= n) siz[u] = 1;
    fa[u][0] = father;
    for (int i = 1; i < N; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : edge[u]) {
        if (v == father) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
}

int check(int u,int v,int mid) {
    for (int i = N - 1; i >= 0; i--)
        if (fa[u][i] > 0 && val[fa[u][i]] <= mid)
            u = fa[u][i];
    for (int i = N - 1; i >= 0; i--)
        if (fa[v][i] > 0 && val[fa[v][i]] <= mid)
            v = fa[v][i];
    if (u == v) return siz[u];
    return siz[u] + siz[v];
}

int query(int u, int v, int z) {
    int l = 1, r = m, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(u, v, mid) >= z) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> E[i].first >> E[i].second;
    for (int i = 1; i <= n; i++)
        f[i] = i;
    cnt = n;
    for (int i = 1; i <= m; i++) {
        int u = find(E[i].first), v = find(E[i].second);
        if (u == v) continue;
        ++cnt;
        f[u] = f[v] = f[cnt] = cnt;
        val[cnt] = i;
        add(cnt, u); add(cnt, v);
    }
    for (int i = 1; i <= cnt; i++)
        if (f[i] == i)
            dfs(i, 0);
    int Q; cin >> Q;
    while (Q--) {
        int x, y, z;
        cin >> x >> y >> z;
        cout << query(x, y, z)<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```

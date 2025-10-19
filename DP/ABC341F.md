首先 由于 $\sum_{y\in S} W_y < W_x$ 所以只有 $W$ 值大的点向 $W$ 值小的点之间才存在有意义的边

那么我们就直接只连有意义的边即可 由于 $>$ 的性质 剩下的图一定是一个 **$DAG$** 也即**有向树**

其实我们可以发现无论一开始的棋子放置的数目如何 都不会影响这个棋子接下来的转移操作

所以我们只需要求出将一个棋子放在每个点上其对答案的贡献为多少

那么当前的棋子显然是可以将自己的棋子转移到其相邻的(子节点)上去

也就是说 假设我们已知子节点对答案的贡献 $val$ 为多少 同时我们又知道每个点的 $W$ 

我们就可以将所有子节点的 $W_{son}$ 视作重量 将 $val$ 视作价值

那么我们要做的就是一个 **将所有子节点视作物品,容量为 $W_{fa} - 1$ 的 $01$ 背包** 另外记得将自己也作为一个贡献加入自己的 $val$

初始条件很显然 所有子节点由于没有可以转移的 其 $val = 1$

那么最后我们计算出每个点上的 $val$ $\times$ 每个点上的棋子数量 求总和即为答案

```cpp
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
#include<random>

using namespace std;

#define int long long
typedef long long ll;

constexpr ll mod = 1e9 + 7;

constexpr int maxn = 2e5 + 10;
constexpr int base = 131;
constexpr int eps = 1e-7;
constexpr int intinf = 1e9 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };

int n, m, u[maxn], v[maxn], w[maxn], val[maxn];

vector<int> edge[maxn];


void add(int u, int v) {
    edge[u].push_back(v);
}

int dfs(int u) {
    if (val[u]) return val[u];
    vector<int> f(w[u]);
    vector<pair<int, int>> goods;
    for (auto v : edge[u]) {
        goods.push_back({ w[v],dfs(v) });
    }
    for (auto [heavy, value] : goods)
        for (int i = w[u] - 1; i >= heavy; i--)
            f[i] = max(f[i - heavy] + value, f[i]);
    val[u] = f[w[u] - 1] + 1;
    return val[u];
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> u[i] >> v[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= m; i++) {
        if (w[u[i]] < w[v[i]]) add(v[i], u[i]);
        if (w[v[i]] < w[u[i]]) add(u[i], v[i]);
    }
    for (int i = 1; i <= n; i++)
        if (!val[i])
            dfs(i);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        ans += x * val[i];
    }
    cout << ans << "\n";
    
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    for (int i = 1; i <= T; i++)
        solve(i);
    return 0;
}
```


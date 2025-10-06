/*
  链接 : https://www.luogu.com.cn/problem/P2962
  先根据题意解方程
  然后 若仅有唯一解 那么直接统计 1 的个数即可
  否则 按照构造解的方法倒着进行 dfs 对每个非主元枚举其为 0 或 1 然后倒着推
  过程中统计 1 的个数 加上剪枝可以过此题
  另外 由于 N = 35 可以使用折半搜索来实现
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
#include<random>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int mod = 1e9 + 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-7;
constexpr int intinf = 1e9 + 10;

#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[40][40], ans, b[40];

void Gauss() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && a[j][j] == 1) continue;
            if (a[j][i] == 1) {
                swap(a[j], a[i]);
            }
        }
        if (a[i][i] == 0) continue;
        for (int j = 1; j <= n; j++)
            if (a[j][i] == 1 && j != i)
                for (int k = 1; k <= n + 1; k++)
                    a[j][k] ^= a[i][k];
    }
}

void dfs(int t, int g) {
    if (g >= ans) return;
    if (t == 0) {
        ans = g;
        return;
    }
    if (a[t][t] == 0) {
        b[t] = 0;
        dfs(t - 1, g);
        b[t] = 1;
        dfs(t - 1, g + 1);
        b[t] = 0;
    }
    else {
        int state = a[t][n + 1];
        for (int i = t + 1; i <= n; i++)
            if (a[t][i] && b[i] == 1) state ^= 1;
        dfs(t - 1, g + state);
    }
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        a[i][i] = 1, a[i][n + 1] = 1;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    Gauss();
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (a[i][i] == 0) {
            flag = false;
            break;
        }
    if (flag) {
        for (int i = 1; i <= n; i++)
            if (a[i][n + 1] == 1) ans++;
        cout << ans << "\n";
    }
    else {
        ans = n;
        dfs(n, 0);
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    for (int id = 1; id <= T; id++) {
        solve(id);
    }
    return 0;
}

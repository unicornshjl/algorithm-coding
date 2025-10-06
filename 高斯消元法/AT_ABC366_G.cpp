/*
  链接 : https://atcoder.jp/contests/abc366/tasks/abc366_g
  按照边信息列异或方程组即可
  考虑如何构造一组解
  大体思路还是按照原本方法倒着做 当我们给一个非主元分配值的时候 由于 N <= 60 我们的给定值 val <= 2^60 
  那么我们不妨把每个自由元定为 (2 ^ cnt ) - 1 这样可以保证每个元之间必定不会有重复关系
  主元仍然是按照方法推出取值即可
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

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[70][70];
ll col[maxn], cnt;

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
                for (int k = 1; k <= n; k++)
                    a[j][k] ^= a[i][k];
    }
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    Gauss();
    for (int i = n; i >= 1; i--) {
        if (a[i][i] == 0) {
            ll cur = 0;
            for (int j = n; j >= i + 1; j--)
                if (a[i][j] == 1) cur ^= col[j];
            if (cur == 0) 
                col[i] = (1ll << (++cnt)) - 1;
            else col[i] = cur;
            continue;
        }
        bool flag = false;
        for (int j = i + 1; j <= n; j++)
            if (a[i][j] == 1) {
                flag = true;
                break;
            }
        if (!flag) {
            cout << "No\n";
            return;
        }
        ll cur = 0;
        for (int j = n; j >= i + 1; j--) 
            if (a[i][j] == 1) {
                if (col[j] == 0) col[j] = (1ll<<(++cnt)) - 1;
                cur ^= col[j];
            }
        col[i] = cur;
    }
    cout << "Yes\n";
    for (int i = 1; i <= n; i++)
        cout << col[i] << " ";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    for (int id = 1; id <= T; id++) {
        solve(id);
    }
    return 0;
}

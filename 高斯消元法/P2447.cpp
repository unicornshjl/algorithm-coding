/*
  链接 : https://www.luogu.com.cn/problem/P2447
  由于必定有解 所以 m >= n 那么我们直接以 m 作为矩阵的行大小即可
  然后根据题意解方程即可
  考虑如何处理需要的信息 可以在找主元列的时候记录下行编号的最大值 这个值即为所需的信息数
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

//#define int long long 
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

bitset<2002> a[2002];

int n, m, need;

void Gauss() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (j < i && a[j][j] == 1) continue;
            if (a[j][i] == 1) {
                need = max(need, j);
                swap(a[i], a[j]);
                break;
            }
        }
        if (a[i][i] == 0) return;
        for (int j = 1; j <= m; j++)
            if (j != i && a[j][i] == 1)
                a[j] ^= a[i];
    }
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        string s; int x; 
        cin >> s >> x;
        for (int j = 0; j < s.length(); j++)
            if (s[j] == '1') a[i].set(j + 1);
        if (x == 1) a[i].set(m + 1);
    }
    Gauss();
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (a[i][i] == 0) {
            flag = false;
            break;
        }
    if (flag) {
        cout << need << "\n";
        for (int i = 1; i <= n; i++)
            if (a[i][m + 1] == 1) cout << "?y7M#\n";
            else cout << "Earth\n";
    }
    else {
        cout << "Cannot Determine\n";
    }
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

/*
  链接 : https://www.luogu.com.cn/problem/P2455
  加法方程组的模板 注意解的判断即可
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
constexpr int mod = 998244353;
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

int n;
ld a[100][100];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        int maxline = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && a[j][j] >= eps) continue;
            if (abs(a[maxline][i]) < abs(a[j][i])) maxline = j;
        }
        swap(a[maxline], a[i]);
        if (abs(a[i][i]) < eps) continue;
        ld tmp = a[i][i];
        for (int j = 1; j <= n + 1; j++) 
            a[i][j] /= tmp;
        for (int j = 1; j <= n; j++) {//消第 j 列
            if (j == i) continue;
            ld tmp = a[j][i];
            for (int k = 1; k <= n + 1; k++) {
                a[j][k] -= tmp * a[i][k];
            }
        }
    }
    bool f1 = false, f2 = true;
    for (int i = 1; i <= n; i++) {
        if (a[i][i] < eps) {
            f1 = true;
            if (abs(a[i][n + 1]) >= eps) f2 = false;
        }
    }
    if (f1) {
        if (!f2) cout << -1 << "\n";
        else cout << 0 << "\n";
    }
    else {
        for (int i = 1; i <= n; i++)
            cout << "x" << i << "=" << fixed << setprecision(2) << a[i][n + 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

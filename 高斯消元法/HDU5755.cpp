/*
  链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5755
  根据题目条件列方程 解出每个格子需要执行多少次操作即可
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
constexpr int mod = 3;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-7;
constexpr int intinf = 1e9 + 10;

#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)

int gcd(int x, int y) {
    return(y == 0 ? x : gcd(y, x % y));
}

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[1000][1000], cnt, ans[1000];

void init(){
    cin >> n >> m;
    cnt = n * m;
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt + 1; j++)
            a[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            int p = (i - 1) * m + j;
            a[p][cnt + 1] = ((mod - x % mod) % mod + mod) % mod;
            a[p][p] = 2;
            for (int k = 0; k < 4; k++) {
                int tx = i + dx[k], ty = j + dy[k];
                if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
                    int q = (tx - 1) * m + ty;
                    a[p][q] = 1;
                }
            }
        }
}

void Gauss() {
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (j < i && a[j][j] != 0) continue;
            if (a[j][i]) {
                swap(a[i], a[j]);
                break;
            }
        }
        if (a[i][i] == 0) continue;
        for (int j = 1; j <= cnt; j++)
            if (j != i && a[j][i] != 0) {
                int g = gcd(a[i][i], a[j][i]);
                int A = a[j][i] / g;
                int B = a[i][i] / g;
                for (int k = 1; k <= cnt + 1; k++) 
                    a[j][k] = ((a[j][k] * B - a[i][k] * A) % mod + mod) % mod;
            }
    }
}

void solve(int id) {
    init();
    Gauss();
    for (int i = 1; i <= cnt; i++) ans[i] = -1;
    for (int i = cnt; i >= 1; i--) {
        int res = a[i][cnt + 1];
        if (a[i][i] == 0) { ans[i] = 0; continue; }
        if (a[i][i] != 0) {
            for (int j = i + 1; j <= cnt; j++)
                if (a[i][j] != 0) {
                    if (ans[j] == -1) ans[j] = 0;
                    res = ((res - ans[j] * a[i][j]) % mod + mod) % mod;
                }
            ans[i] = res * inv(a[i][i]) % mod;
        }
    }
    int sum = 0;
    for (int i = 1; i <= cnt; i++)
        sum += ans[i];
    cout << sum << "\n";
    for (int i = 1; i <= cnt; i++)
        if (ans[i] != 0) {
            int x = (i - 1) / m + 1, y = (i - 1) % m + 1;
            for (int j = 1; j <= ans[i]; j++)
                cout << x << " " << y << "\n";
        }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int id = 1; id <= T; id++) {
        solve(id);
    }
    return 0;
}

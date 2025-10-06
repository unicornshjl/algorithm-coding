/*
    链接 : https://www.luogu.com.cn/problem/P10315
    根据题意列出方程 构造出一组解即可
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

#define int long long 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int mod = 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-7;
constexpr int intinf = 1e9 + 10;

#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)

int gcd(int x, int y) {
    return(y == 0 ? x : gcd(y, x % y));
}

int lowbit(int x) {
    return x & (-x);
}

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[110][110], b[110], ans[110];

int ksm(int a, int b) {
    if (b < 0) return 0;
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int inv(int x) {
    return ksm(x, m - 2);
}

void Gauss() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && a[j][j] != 0) continue;
            if (a[j][i]) {
                swap(a[j], a[i]);
                break;
            }
        }
        if (a[i][i] == 0) continue;
        for (int j = 1; j <= n; j++)
            if (a[j][i] != 0 && j != i) {
                int g = gcd(a[i][i], a[j][i]);
                int A = a[i][i] / g;
                int B = a[j][i] / g;
                for (int k = 1; k <= n + 1; k++)
                    a[j][k] = ((a[j][k] * A - a[i][k] * B) % m + m) % m;
            }
    }
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i][i] = 1;
        for (int j = 1; j <= x; j++) {
            int y; cin >> y;
            a[y][i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i][n + 1] = ((x - b[i]) % m + m) % m;
    }
    Gauss();
    for (int i = 1; i <= n; i++) {
        if (a[i][i] == 0 && a[i][n + 1]) {
            cout << "niuza\n";
            return;
        }
    }
    for (int i = 1; i <= n; i++)
        ans[i] = -1;
    for (int i = n; i >= 1; i--) {
        if (a[i][i] == 0) {
            ans[i] = 1;
            continue;
        }
        else {
            int res = a[i][n + 1];
            for (int j = i + 1; j <= n; j++)
                if (a[i][j] != 0) {
                    if (ans[j] == -1) ans[j] = 0;
                    res = ((res - ans[j] * a[i][j] % m) % m + m) % m;
                }
            ans[i] = res * inv(a[i][i]) % m;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //cin >> T;
    while (T--) {
        solve(T);
    }
    return 0;
}

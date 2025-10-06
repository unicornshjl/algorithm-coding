/*
  链接 : https://vjudge.net/problem/POJ-2947
  根据题意列方程即可
  但是本题中 方程数 和 元的数量 不同 那么我们采用的策略是 "缺啥补啥"
  不妨直接设 N = max(n , m); 让矩阵大小为 N 行 N + 1 列
  然后就可以正常高斯消元 正常判断解的情况了
  注意此题最终解出来之后还要对应去找工作的天数
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
constexpr int mod = 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-7;
constexpr int intinf = 1e9 + 10;

#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)

int gcd(int x, int y) {
    return(y == 0 ? x : gcd(y, x % y));
}

int inv(int x) {
    return ksm(x, mod - 2);
}
constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[500][500], ans[8], s;

map<string, int> mp;

void prework() {
    mp["MON"] = 1;
    mp["TUE"] = 2;
    mp["WED"] = 3;
    mp["THU"] = 4;
    mp["FRI"] = 5;
    mp["SAT"] = 6;
    mp["SUN"] = 7;
    ans[0] = 7;
    ans[1] = 8;
    ans[2] = 9;
    ans[3] = 3;
    ans[4] = 4;
    ans[5] = 5;
    ans[6] = 6;
}

void Gauss() {
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= s; j++) {
            if (j < i && a[j][j] != 0) continue;
            if (a[j][i]) {
                swap(a[j], a[i]);
                break;
            }
        }
        if (a[i][i] == 0) continue;
        for (int j = 1; j <= s; j++) 
            if (a[j][i] != 0 && j != i) {
                int g = gcd(a[i][i], a[j][i]);
                int A = a[j][i] / g;
                int B = a[i][i] / g;
                for (int k = 1; k <= s + 1; k++) 
                    a[j][k] = ((a[j][k] * B - a[i][k] * A) % mod + mod) % mod;
            }
    }
}

void solve(int id) {
    s = max(m, n);
    for (int i = 1; i <= s; i++)
        for (int j = 1; j <= s + 1; j++)
            a[i][j] = 0;
    for (int i = 1; i <= m; i++) {
        int g; string st, ed;
        cin >> g >> st >> ed;
        int x = mp[st], y = mp[ed] + 7;
        a[i][s + 1] = ((y - x + 1) % mod + mod) % mod;
        while (g--) {
            int x; cin >> x; 
            a[i][x]++;
        }
    }
    Gauss();
    int g = 0;
    int flag = 0;
    for (int i = 1; i <= s; i++) {
        if (i <= n && a[i][i] == 0) {
            flag = 1;
        }
        if (a[i][i] == 0 && a[i][s + 1] != 0) {
            cout << "Inconsistent data.\n";
            return;
        }
    }
    if (flag == 1) cout << "Multiple solutions.\n";
    else {
        for (int i = 1; i <= n; i++) {
            int x = a[i][s + 1] * inv(a[i][i]) % mod;
            cout << ans[x] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    prework();
    cin >> n >> m;
    while (n && m) {
        solve(1);
        cin >> n >> m;
    }
    return 0;
}

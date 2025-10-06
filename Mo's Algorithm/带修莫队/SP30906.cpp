/*
  链接 : https://www.luogu.com.cn/problem/SP30906
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
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;
 
 
constexpr int maxn = 5e5 + 10;
constexpr int N = 25;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16
 
int n, m, a[maxn], num, cnt, res[maxn], ans, f[maxn];
 
struct Ch {
    int p, x;
} Q[maxn];
 
struct node {
    int l, r, kl, kr, id, t;
} q[maxn];
 
bool cmp(node c1, node c2) {
    if (c1.kl == c2.kl) {
        if (c1.kr == c2.kr)
            return c1.t < c2.t;
        return c1.kr < c2.kr;
    }
    return c1.kl < c2.kl;
}
 
void add(int x) {
    f[x]++;
    if (f[x] == 1) ans++;
    if (f[x] == 2) ans--;
}
 
void dec(int x) {
    f[x]--;
    if (f[x] == 1) ans++;
    if (f[x] == 0) ans--;
}
 
void update(int l, int r, int t) {
    int p = Q[t].p, x = Q[t].x;
    if (p >= l && p <= r) {
        add(x); dec(a[p]);
    }
    swap(a[p], Q[t].x);
}
 
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int B = (int)(pow(n, 2.0 / 3));
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            x++;
            Q[++num].p = x;
            Q[num].x = y;
        }
        else {
            int l, r;
            cin >> l >> r;
            l++; r++;
            q[++cnt].l = l; q[cnt].r = r; q[cnt].id = cnt;
            q[cnt].kl = (l - 1) / B + 1; q[cnt].kr = (r - 1) / B + 1; q[cnt].t = num;
        }
    }
    sort(q + 1, q + cnt + 1, cmp);
    int l = 1, r = 0, T = 0;
    for (int i = 1; i <= cnt; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) dec(a[l++]);
        while (r > q[i].r) dec(a[r--]);
        while (T < q[i].t) update(q[i].l, q[i].r, ++T);
        while (T > q[i].t) update(q[i].l, q[i].r, T--);
        res[q[i].id] = ans;
    }
    for (int i = 1; i <= cnt; i++)
        cout << res[i] << "\n";
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

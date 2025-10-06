/*
    还是利用普通莫队统计出现次数
    稍微把题目中要求的式子转化一下即可
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

#define lson(x) x << 1
#define rson(x) x << 1 | 1

ll gcd(ll x, ll y) {
    return(y == 0 ? x : gcd(y, x % y));
}

ll ksm(ll a, ll b) {
    if (b < 0) return 0;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a;// % mod;
        a = a * a;// % mod;
        b >>= 1;
    }
    return res;
}

constexpr int maxn = 5e5 + 10;
constexpr int N = 25;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43};
//these primes' product > 1e16

int n, m, a[maxn], B;
ll ans, f[maxn];
pair<ll, ll> res[maxn];

void add(int x) {
    ans -= f[x] * f[x];
    f[x]++;
    ans += f[x] * f[x];
}

void dec(int x) {
    ans -= f[x] * f[x];
    f[x]--;
    ans += f[x] * f[x];
}

struct node {
    int l, r, k, id;
} q[maxn];

bool cmp(node c1, node c2) {
    if (c1.k == c2.k) return c1.r > c2.r;
    return c1.k < c2.k;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    B = sqrt(n);
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].k = (q[i].l - 1) / B + 1;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, cmp);
    ans = 0;
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (q[i].l < l) add(a[--l]);
        while (q[i].r > r) add(a[++r]);
        while (q[i].l > l) dec(a[l++]);
        while (q[i].r < r) dec(a[r--]);
        ll len = q[i].r - q[i].l + 1;
        ll P = ans - len;
        ll Q = len * (len - 1);
        if (Q == 0) res[q[i].id] = { 0,1 };
        else {
            ll G = gcd(P, Q);
            P /= G, Q /= G;
            res[q[i].id] = { P,Q };
        }
    }
    for (int i = 1; i <= m; i++)
        cout << res[i].first << "/" << res[i].second << "\n";
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

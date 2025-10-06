/*
  链接 : https://www.luogu.com.cn/problem/P4688
  考虑如何处理同时在三个区间中除去某些数字
  我们可以将这三个区间分开考虑 对每个区间去生成一个 bitset
  每个 bitset 表示数字的出现状态 
  如何处理 ? 我们首先对这些数字进行离散化 但是不去重
  记 x 出现次数为 f[x] 那么当 x 出现时 我们将 bitset上的 x + f[x] - 1 位设置为 1
  那么对于一个询问 我们会得到三个区间的 bitset state1 state2 state3 
  令state = state1 & state2 & state3 
  可以发现 state 上所有为 1 的位置就是可以共同删除的
  
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

constexpr int maxn = 1e5 + 10;
constexpr int N = 23;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[maxn], b[maxn], cnt, f[maxn], res[maxn], g[maxn];

bitset<100001> st[10010][3], cur;

struct node {
    int l, r, bl, id;
} q[maxn];

bool cmp(node c1, node c2) {
    if (c1.bl == c2.bl) {
        if (c1.bl & 1) return c1.r < c2.r;
        return c1.r > c2.r;
    }
    return c1.bl < c2.bl;
}

void add(int x) {
    cur.set(x + f[x]);
    f[x]++;
}

void del(int x) {
    f[x]--;
    cur.reset(x + f[x]);
}

void disc() {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
}

void solve(int id) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    disc();
    int MAX = 1e4, B = sqrt(n);
    while (m > 0) {
        cur.reset();
        for (int i = 1; i <= n; i++) f[i] = 0;
        cnt = 0;
        for (int i = 1; i <= min(m, MAX); i++) {
            g[i] = 0; res[i] = 0;
            for (int j = 1; j <= 3; j++) {
                int l, r;
                cin >> l >> r;
                q[++cnt] = { l,r,(l - 1) / B + 1,i };
                res[i] += r - l + 1;
            }
        }
        sort(q + 1, q + cnt + 1, cmp);
        int l = 1, r = 0;
        for (int i = 1; i <= cnt; i++) {
            while (l > q[i].l) add(a[--l]);
            while (r < q[i].r) add(a[++r]);
            while (l < q[i].l) del(a[l++]);
            while (r > q[i].r) del(a[r--]);
            st[q[i].id][g[q[i].id]] = cur;
            g[q[i].id]++;
        }
        for (int i = 1; i <= min(m, MAX); i++) {
            bitset<100001> x = st[i][0];
            x &= st[i][1];
            x &= st[i][2];
            res[i] -= x.count() * 3;
            cout << res[i] << "\n";
        }
        m -= MAX;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve(T);
    }
    return 0;
}

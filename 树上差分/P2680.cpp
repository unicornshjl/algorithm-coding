首先看到题设想到二分 然后

#include<iostream>
#include<cmath>
#include<cstdio>
#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<utility>
#include<unordered_map>
#include<unordered_set>
#include<bitset> 
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int maxn = 3e5 + 10;
constexpr int maxm = 6e6 + 10;
constexpr int intinf = 1e9 + 10;
constexpr int mod = 998244353;
constexpr ll mods[] = { 998244353,1000000007,1000000009 };
constexpr ll inf = 1e15 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
constexpr ld eps = 1e-12;
using namespace std;
int qu[maxn], qv[maxn], n, m, f[maxn], ans[maxn], dis[maxn], d[maxn], val[maxn], sum[maxn], cnt, w[maxn];
bool vis[maxn];
int cnt1, cnt2, to1[maxn << 1], to2[maxn << 1], head1[maxn], head2[maxn], id1[maxn << 1], v1[maxn << 1], v2[maxn << 1], nxt1[maxn << 1], nxt2[maxn << 1];
inline void add1(int u, int v, int w, int id) {
	to1[++cnt1] = v; nxt1[cnt1] = head1[u]; head1[u] = cnt1; v1[cnt1] = w; id1[cnt1] = id;
}

inline void add2(int u, int v, int w) {
	to2[++cnt2] = v; nxt2[cnt2] = head2[u]; head2[u] = cnt2; v2[cnt2] = w;
}

inline int find(int x) {
	return(x == f[x] ? x : f[x] = find(f[x]));
}

inline int read()
{
	char c = getchar(); int x = 0;
	while (c < '0' || c>'9')	c = getchar();
	while (c >= '0' && c <= '9')	x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x;
}

inline void init() {
	n = read(), m = read();
	for (int i = 1; i < n; i++) {
		int u, v;
		u = read(), v = read(), w[i] = read();
		add1(u, v, w[i], i);
		add1(v, u, w[i], i);
	}
	for (int i = 1; i <= m; i++) {
		qu[i] = read(), qv[i] = read();
		add2(qu[i], qv[i], i);
		add2(qv[i], qu[i], i);
	}
	for (int i = 1; i <= n; i++) f[i] = i;
}

inline void tarjan(int u, int fa) {
	vis[u] = 1;
	for (int i = head1[u]; i; i = nxt1[i]) {
		int v = to1[i], w = v1[i], id = id1[i];
		if (v == fa) continue;
		dis[v] = dis[u] + w;
		tarjan(v, u);
		f[v] = u;
	}
	for (int i = head2[u]; i; i = nxt2[i]) {
		int v = to2[i], num = v2[i];
		if (vis[v] && !ans[num])	ans[num] = find(v);
	}
}

inline void dfs(int u, int fa) {
	for (int i = head1[u]; i; i = nxt1[i]) {
		int v = to1[i], w = v1[i], id = id1[i];
		if (v == fa) continue;
		dfs(v, u);
		val[id] += sum[v];
		sum[u] += sum[v];
	}
}

inline bool check(int mid) {
	cnt = 0;
	for (int i = 1; i <= n; i++)
		val[i] = sum[i] = 0;
	int res = 0;
	for (int i = 1; i <= m; i++) {
		if (d[i] <= mid) continue;
		cnt++;
		sum[qu[i]]++; sum[qv[i]]++; sum[ans[i]] -= 2;
		res = max(res, d[i]);
	}
	if (cnt == 0) return true;
	dfs(1, 0);
	for (int i = 1; i < n; i++)
		if (val[i] == cnt && res - w[i] <= mid) return true;
	return false;
}

inline void solve() {
	for (int i = 1; i <= m; i++)
		d[i] = dis[qu[i]] + dis[qv[i]] - 2 * dis[ans[i]];
	int l = 0, r = 300000000, res;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << res << "\n";
}

int main() {
	init();
	tarjan(1, 0);
	solve();
	return 0;
}

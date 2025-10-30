这是线性基应用 A 利用普通消元法得到一组线性基 然后得到异或和最大值的模板
原理已经讲的很清楚了 我们主要对这个过程进行注释 确保细节无误

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
constexpr int maxn = 2e5 + 10;
constexpr int maxm = 64 + 10;
constexpr int intinf = 1e9 + 10;
constexpr int mod = 998244353;
constexpr ll inf = 1e15 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
constexpr ld eps = 1e-8;
using namespace std;

int n;
ll a[maxn], base[maxm];

void init() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
}

bool insert(ll x) {
	for (int i = 50; i >= 0; i--)
		if ((x >> i) & 1) {
			if (base[i] == 0) {
				base[i] = x;
				return true;
			}
			else x ^= base[i];
			if (x == 0) return false;
		}
}

void solve() {
	bool zero = false;
	for (int i = 1; i <= n; i++) {
		if (!insert(a[i])) 
			zero = true;
	}
	ll ans = 0;
	for (int i = 50; i >= 0; i--)
		ans = max(ans, ans ^ base[i]);
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	init();
	solve();
	return 0;
}

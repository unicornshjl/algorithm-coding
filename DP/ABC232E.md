这类求方案数的题目很容易想到 $DP$ 

一个最朴素的想法是设 $f_{i,j,k}$ 表示当前走了 $k$ 步 位置在 $i,j$ 那么初始状态为 $f_{x1,y1,0} = 1$ 答案即为 $f_{x2,y2,K}$ 

转移是简单的 $f_{i,j,k} = \sum f_{i,j',k - 1} + \sum f_{i',j,k - 1}$ 

其中 $j'$ 为除了 $j$ 之外列的所有取值 $i'$ 是除了 $i$ 之外其他i的所有取值

但是由于 $H,W$ 会达到 $10^9$ 的规模 $K$ 会达到 $10^6$ 的规模 所以此做法显然复杂度过大

我们发现 每次转移的过程中 **只有和 $i,j$ 同行或同列的格子会转移过来 而其他格子的状态我们是不关心的**

也就是说我们的状态实际上有很多冗余

那么很自然的 我们想到优化一下状态设计 显然 $k$ 是无法被优化掉的 而由于只有行或列会影响的性质 我们可以这样设计状态

$f_{k,0}$ 表示走了 $k$ 步 后与 $x_2,y_2$ 同行同列的状态数

$f_{k,1}$ 表示走了 $k$ 步 后与 $x_2,y_2$ 仅行相同的状态数

$f_{k,2}$ 表示走了 $k$ 步 后与 $x_2,y_2$ 仅列相同的状态数

$f_{k,3}$ 表示走了 $k$ 步 后与 $x_2,y_2$ 行列均不同的状态数

那么显然答案是 $f_{K,0}$ 而初始状态根据 $x1,y1$ 与 $x2,y2$ 的关系确定

考虑转移

由于只有**和当前行相同的行或者列**能够到达**行相同列相同** 所以 $f_{k,0} = f_{k - 1, 1} + f_{k - 1,2}$ 

**行列均不同**的状态可以移动一步到达**行相同**的状态 而**行相同列不同**的状态 到达该列的任意位置使得**行相同列不同** 而由于不能停在原地 也不能转移到行列均相同的位置去 所以 $f_{k,1} = f_{k - 1,1} \times (W - 2) + f_{k - 1,3}$

同理 可以得出 $f_{k,2} = f_{k - 1,2} \times (H - 2) + f_{k - 1,3}$

而**行相同列不同**的状态可以移动到该行的任意位置使得**行不同列不同** 但是不能停在原地 **列相同行不同**的状态也可以移动到该列的任意位置使得**行不同列不同** 但是不能停在原地 **行不同列不同**的状态 一步行移动或者列移动都可以使它们到达**行不同列不同**的状态 但是行不能移动到当前行 列不能移动到当前列 所以 $f_{k,3} = (H - 1) \times f_{k - 1,1} + (W - 1) \times f_{k - 1,2} + (H - 1 + W - 1) \times f_{k - 1,3}$

另外 不要忘记取模



所以代码如下 : 

```cpp
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
constexpr int maxn = 1e6 + 10;
constexpr int maxm = 1000 + 10;
constexpr ll mod = 998244353;
constexpr ll mod1 = 1e9 + 7;
constexpr ll mods[] = { 998244353,1000000007,1000000009 };
constexpr ll inf = 1e18 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
constexpr ld eps = 1e-12;
using namespace std;
ll h, w, k, sx, sy, ex, ey, f[maxn][5];
void init() {
	cin >> h >> w >> k;
	cin >> sx >> sy >> ex >> ey;
	if (sx == ex && sy == ey) f[0][0] = 1;
	else if (sx == ex && sy != ey) f[0][1] = 1;
	else if (sx != ex && sy == ey) f[0][2] = 1;
	else f[0][3] = 1;
}
void solve() {
	for (int i = 1; i <= k; i++) {
		f[i][0] = (f[i - 1][1] + f[i - 1][2]) % mod;
		f[i][1] = (f[i - 1][3] % mod + (f[i - 1][1]) * (w - 2) % mod + (f[i - 1][0]) * (w - 1) % mod) % mod;
		f[i][2] = (f[i - 1][3] % mod + (f[i - 1][2]) * (h - 2) % mod + (f[i - 1][0]) * (h - 1) % mod) % mod;
		f[i][3] = ((h - 1) * (f[i - 1][1]) % mod + (w - 1) * (f[i - 1][2]) % mod + (h + w - 4) * (f[i - 1][3]) % mod) % mod;
	}
	cout << f[k][0] % mod << "\n";
}
int main() {
	init();
	solve();
	return 0;
}
```


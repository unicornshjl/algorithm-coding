测试连接 : https://loj.ac/p/114
本题为线性基应用 B 利用高斯消元构造出标准线性基 得到第 k 小异或和的模板题
思路已经讲的很清了 通过注释来保证细节无误

#include <iostream>
#include <cmath>
#include <cstdio>
#include <random>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int maxn = 2e5 + 10;
constexpr int maxm = 64 + 10;
constexpr int intinf = 1e9 + 10;
constexpr int mod = 998244353;
constexpr ll inf = 1e15 + 10;
constexpr int dx[] = { 1, -1, 0, 0 };
constexpr int dy[] = { 0, 0, 1, -1 };
constexpr ld eps = 1e-8;
using namespace std;

int n, pos;
ll base[maxn];
bool zero;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> base[i];
}

bool Gauss() {
    pos = 1;//pos 就是 len 
    for (int i = 50; i >= 0; i--) {//当前考虑第 i 位
        for (int j = pos; j <= n; j++)//从第 pos 为开始
            if ((base[j] >> i) & 1) {//第 j 个元素的第 i 位为 1 
                swap(base[pos], base[j]);
                break;
            }

        if ((base[pos] >> i) & 1) {//当前位为 1 
            for (int j = 1; j <= n; j++)
                if (pos != j && ((base[j] >> i) & 1)) {
                    base[j] ^= base[pos];//高斯消元 其他当前位为 1 元素都要进行异或
                }

            pos++;
        }
        //需要注意 就算当前位没有基 pos 也不需要后移
    }

    pos--;//pos 始终会多右移一位 所以我们要把其左移一位得到正确的位置
    //pos 是线性基的大小 表明从 pos + 1 到 n 实际上与线性基异或后都会变为 0 也就是意味着只有 pos == n 的时候 恰好是线性无关组 无法生成出 0
    return pos != n;
}

ll query(ll p) {
    if (zero)
        p--;//如果能构造出 0 那么 0 一定是第 1 小 所以 p--

    if (p >= (1ll << pos))
        return -1;//如果比能构造出来的元素个数上限还要多 就返回 -1

    ll res = 0;

    for (int i = pos, j = 0; i >= 1; i--, j++)// j 表示 p 的第 j 位是否为 1 而 i 和 j 相对称的原因是 线性基是从高位向低位构造的 但是求第 p 小是从低位到高位进行的
        if ((p >> j) & 1)
            res ^= base[i];

    return res;
}

void solve() {
    zero = Gauss();//利用高斯消元得到标准基 zero 表示是否能构造出 0 
    int Q;
    cin >> Q;
    while (Q--) {
        ll p;
        cin >> p;
        cout << query(p) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}

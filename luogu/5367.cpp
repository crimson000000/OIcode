#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10, mod = 998244353;
ll fact[N];
ll res;
ll a[N];
int n;

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(n);

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ ) bit.add(i, 1);

    res = 1;
    for(int i = 1; i <= n; i ++ )
    {
        bit.add(a[i], -1);
        // cout << bit.query(a[i]) << endl;
        res = (res + bit.query(a[i]) * fact[n - i] % mod) % mod;
    }

    cout << res << endl;

    return 0;
}

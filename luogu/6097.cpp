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

const int N = 2e6 + 10, mod = 1e9 + 9;
ll f[22][N], g[22][N], h[22][N];
ll n, lim;

inline int popc(int x)
{
    return __builtin_popcount(x);
}

inline void OR(ll a[], int n, int op)
{
    for(int m = 2; m <= n; m <<= 1)
        for(int k = 0; k < n; k += m)
            for(int j = 0; j < m / 2; j ++ )
                a[j + k + m / 2] = (a[j + k + m / 2] + a[j + k] * op + mod) % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    lim = n;
    n = 1 << n;

    for(int i = 0; i < n; i ++ ) f[popc(i)][i] = read();
    for(int i = 0; i < n; i ++ ) g[popc(i)][i] = read();

    for(int i = 0; i <= lim; i ++ )
        OR(f[i], n, 1), OR(g[i], n, 1);

    for(int i = 0; i <= lim; i ++ )
        for(int j = 0; j <= i; j ++ )
            for(int k = 0; k < n; k ++ )
                h[i][k] = (h[i][k] + f[j][k] * g[i - j][k] % mod) % mod;
    
    for(int i = 0; i <= lim; i ++ )
        OR(h[i], n, -1);

    for(int i = 0; i < n; i ++ ) printf("%lld ", h[popc(i)][i]);

    return 0;
}

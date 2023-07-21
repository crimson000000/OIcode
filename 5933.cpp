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

const int N = 20 + 10, mod = 1e9 + 7;
ll f[1 << 16], g[1 << 16];
ll c[N][N];
int n;

inline int lowbit(int x)
{
    return x & -x;
}

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
        for(int j = 1; j <= n; j ++ ) 
            c[i][j] = read();

    for(int s = 0; s < (1 << n); s ++ )
    {
        g[s] = 1;
        for(int i = 1; i <= n; i ++ )
            for(int j = i + 1; j <= n; j ++ )
                if((s >> (i - 1) & 1) && (s >> (j - 1) & 1))
                    g[s] = g[s] * (c[i][j] + 1) % mod;
    }               

    for(int s = 0; s < (1 << n); s ++ )
    {
        int p = lowbit(s);
        f[s] = g[s];
        for(int t = (s - 1) & s; t; t = s & (t - 1))
        {
            if(t & p)
                f[s] = (f[s] - f[t] * g[s ^ t] % mod + mod) % mod;
        }
    }

    cout << f[(1 << n) - 1] << endl;

    return 0;
}

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

const int N = 1e6 + 10, mod = 1e9 + 7;
ll fact[N], invfact[N];
ll c[N];
ll f[N], g[N];
ll ans;
int n, m;

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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod; 
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n; i >= 1; i -- ) invfact[i - 1] = invfact[i] * i % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        c[i] = read();
        n += c[i];
    }
    
    init(n);

    f[0] = 1;
    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 0; j <= n; j ++ ) g[j] = 0;
        for(int j = 0; j <= n; j ++ )
            if(f[j])
                for(int k = 0; k < c[i]; k ++ )
                    g[j + k] = (g[j + k] + f[j] * C(c[i] - 1, k) % mod * invfact[c[i] - k] % mod) % mod;
        for(int j = 0; j <= n; j ++ ) f[j] = g[j];
    }

    for(int i = 0; i <= n; i ++ )
    {
        ll tmp = f[i] * fact[n - i] % mod;
        if(i & 1)
            ans = (ans - tmp + mod) % mod;
        else ans = (ans + tmp) % mod;
    }

    cout << ans << endl;

    return 0;
}

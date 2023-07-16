#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 1e9 + 7;
int ch[N][2];
ll fact[N], invfact[N];
ll f[1010][1010];
int stk[N], tt;
int siz[N];
int h[N];
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
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

inline void dfs(int u, int pre)
{
    siz[u] = 1;
    f[u][0] = 1;
    for(int i = 0; i < 2; i ++ )
    {
        int v = ch[u][i];
        if(!v) continue;
        dfs(v, h[u]);
        siz[u] += siz[v];
        for(int j = min(siz[u], m); j >= 0; j -- )
            for(int k = 1; k <= min(j, siz[v]); k ++ )
                f[u][j] = (f[u][j] + f[v][k] * f[u][j - k] % mod) % mod;
    }

    int val = h[u] - pre;
    for(int i = min(siz[u], m); i >= 0; i -- )
        for(int j = 1; j <= min(i, val); j ++ )
            f[u][i] = (f[u][i] + f[u][i - j] * fact[j] % mod * C(siz[u] - i + j, j) % mod * C(val, j) % mod) % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(N - 5);

    for(int i = 1; i <= n; i ++ ) h[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        while(tt > 0 && h[stk[tt]] > h[i]) ch[i][0] = stk[tt -- ];
        if(tt) ch[stk[tt]][1] = i;
        stk[++ tt] = i;
    }

    dfs(stk[1], 0);

    cout << f[stk[1]][m] << endl;

    return 0;
}

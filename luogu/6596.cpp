#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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

const int N = 60, mod = 1e9 + 7;
ll f[N][N]; // i 个点，j 条割边方案数
ll g[N][N][N]; //  i 个点，j 条割边，k 个连通块方案数
ll c[N]; // 有标号无向连通图数量
ll fact[N], invfact[N];
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
    if(m > n || n < 0 || m < 0) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

inline ll graph(ll n)
{
    if(!n) return 1;
    return qmi(2, n * (n - 1) / 2, mod);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(N - 5);
    m = min(m, n - 1);

    c[0] = 1;
    for(int i = 1; i <= n; i ++ )    
    {
        c[i] = graph(i);
        for(int j = 1; j < i; j ++ )
            c[i] = (c[i] - C(i - 1, j - 1) * c[j] % mod * graph(i - j) % mod + mod) % mod;
        // cout << c[i] << endl;
    }

    g[0][0][0] = 1;

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j < i; j ++ )
        {
            for(int p = 1; p <= i - 1; p ++ )
            {
                ll tmp = 0;
                for(int q = 1; q <= min(j, i - p); q ++ )
                    tmp = (tmp + g[i - p][j - q][q] * qmi(p, q, mod) % mod) % mod;
                f[i][j] = (f[i][j] + f[p][0] * C(i - 1, p - 1) % mod * tmp % mod) % mod; 
            }
        }

        f[i][0] = c[i];
        for(int j = 1; j < i; j ++ )
            f[i][0] = (f[i][0] - f[i][j] + mod) % mod;

        for(int j = 0; j < i; j ++ )
        {
            // g[i][j][0] = 1;
            for(int k = 1; k <= i; k ++ )
            {
                for(int p = 1; p <= i; p ++ )
                {
                    for(int q = 0; q <= j; q ++ )
                    {
                        g[i][j][k] = (g[i][j][k] + f[p][q] * p % mod * C(i - 1, p - 1) % mod * g[i - p][j - q][k - 1] % mod) % mod;
                    }
                }
            }
        }
    }

    ll ans = 0;
    for(int i = 0; i <= m; i ++ ) 
    {
        ans = (ans + f[n][i]) % mod;
        // cout << f[n][i] << ' ';
    }
    cout << ans << endl;

    return 0;
}
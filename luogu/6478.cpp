#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e6 + 10, mod = 998244353;
int h[N], e[N], ne[N], idx;
int n;
char s[N];
int siz[N], A[N], B[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
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

ll fact[N], invfact[N];
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

ll f[5010][5010];
ll g[N];
inline void dfs1(int u, int fa)
{
    if(s[u] == '0') A[u] ++;
    else B[u] ++;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        B[u] += B[v];
        A[u] += A[v];
    }
}

inline void dfs(int u, int fa)
{
    f[u][0] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u);

        for(int j = 0; j <= siz[u] + siz[v]; j ++ ) g[j] = 0;
        
        for(int j = 0; j <= siz[u]; j ++ )
            for(int k = 0; k <= siz[v]; k ++ )
                g[j + k] = (g[j + k] + f[u][j] * f[v][k] % mod) % mod;

        siz[u] += siz[v];
        for(int j = 0; j <= siz[u]; j ++ ) f[u][j] = g[j];
    }

    if(s[u] == '0')
    {
        for(int i = siz[u]; i >= 0; i -- )
            if(B[u] - i > 0)
                f[u][i + 1] = (f[u][i + 1] + f[u][i] * (B[u] - i) % mod) % mod;
    }
    else
    {
        for(int i = siz[u]; i >= 0; i -- )
            if(A[u] - i > 0)
                f[u][i + 1] = (f[u][i + 1] + f[u][i] * (A[u] - i) % mod) % mod;
    }
    if(f[u][siz[u] + 1]) siz[u] ++;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();
    init(n);
    scanf("%s", s + 1);

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs(1, 1);

    for(int i = 0; i <= siz[1]; i ++ )
        g[i] = f[1][i] * fact[n / 2 - i] % mod;
    
    for(int i = 0; i <= n / 2; i ++ )
    {
        ll ans = 0;
        for(int j = i; j <= siz[1]; j ++ )
        {
            if((j - i) & 1) ans = (ans + (mod - 1) * C(j, i) % mod * g[j] % mod) % mod;
            else ans = (ans + C(j, i) * g[j] % mod) % mod;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
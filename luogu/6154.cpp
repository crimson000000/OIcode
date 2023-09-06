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
ll f[N], g[N];
int h[N], e[N], ne[N], idx;
int n, m;

ll qmi(ll a, ll k, ll p)
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

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dp(int u)
{
    if(g[u]) return;
    g[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        dp(v);
        g[u] = (g[u] + g[v]) % mod;
        f[u] = (f[u] + f[v] + g[v]) % mod;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b);
    }

    for(int i = 1; i <= n; i ++ )
        if(!g[i])
            dp(i);
    
    ll sum = 0, cnt = 0;
    for(int i = 1; i <= n; i ++ ) 
    {
        sum = (sum + f[i]) % mod;
        cnt = (cnt + g[i]) % mod;
    }

    printf("%lld\n", sum * qmi(cnt, mod - 2, mod) % mod);

    return 0;
}
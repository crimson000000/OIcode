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

const int N = 5050 + 10, mod = 1e9 + 7;
int f[N];
ll g[N];
ll fact[N], invfact[N];
int n, k;
int a[N];

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

inline void solve()
{
    for(int i = 1; i <= n; i ++ ) f[i] = g[i] = 0;

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    int now = 0, maxn = -1;
    g[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        now = 0;
        for(int j = i; j >= 0; j -- )
        {
            if(now >= k)
            {
                if(f[j] + k > f[i])
                {
                    f[i] = f[j] + k;
                    g[i] = g[j] * C(now - 1, k - 1) % mod;
                }
                else if(f[j] + k == f[i])
                    g[i] = (g[i] + g[j] * C(now - 1, k - 1) % mod) % mod;
            }
            if(a[j] == a[i]) now ++;
        }
        maxn = max(maxn, f[i]);
    }

    ll ans = 0;
    for(int i = 0; i <= n; i ++ )
        if(maxn == f[i])
            ans = (ans + g[i]) % mod;
    
    printf("%lld\n", ans);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 10);

    int T = read();
    while(T -- ) solve();

    

    return 0;
}
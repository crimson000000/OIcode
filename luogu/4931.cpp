#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;
typedef __int128 i128;

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

const int N = 5e6 + 10, mod = 998244353;
ll f[N], fact[N], invfact[N];
int n, k;

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
    f[0] = 1, f[1] = 0;
    for(int i = 1; i <= n; i ++ ) 
        f[i + 1] = qmi(i + 1, mod - 2, mod) * (8 * f[i - 1] % mod + 4 * i % mod * f[i] % mod) % mod;
} 


signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(N - 5);

    while(T -- )
    {
        n = read(), k = read();
        printf("%lld\n", fact[n] * fact[n] % mod * qmi(2, k, mod) % mod * invfact[k] % mod * f[n - k] % mod);
    }
    
    return 0;
}
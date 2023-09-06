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

const int N = 1e6 + 10, mod = 167772161;
ll F[N], G[N];
ll fact[N], invfact[N];
int lim, len;
int rev[N];
ll n, k;

inline void calc()
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
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

inline void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        ll m = 1 << dep;
        ll gn = qmi(opt == 1 ? 3 : qmi(3, mod - 2, mod), (mod - 1) / m, mod);
        for(int k = 0; k < lim; k += m)
        {
            ll g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                ll t = a[j + k + m / 2] * g % mod;
                ll u = a[j + k];
                a[j + k] = (u + t) % mod;
                a[j + k + m / 2] = (u - t + mod) % mod;
                g = g * gn % mod;
            }
        }
    }
    if(opt == -1)
    {
        ll inv = qmi(lim, mod - 2, mod);
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * inv % mod;
    }
}

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n; i >= 1; i -- ) invfact[i - 1] = invfact[i] * i % mod;
}

inline void ksm(ll a[], ll b[], ll k)
{
    b[0] = 1;
    while(k)
    {
        NTT(a, 1);
        if(k & 1)
        {
            NTT(b, 1);
            for(int i = 0; i < lim; i ++ )
                b[i] = b[i] * a[i] % mod;
            NTT(b, -1);
            for(int i = n; i < lim; i ++ ) b[i] = 0;
        }
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * a[i] % mod;
        NTT(a, -1);
        for(int i = n; i < lim; i ++ ) a[i] = 0;
        k >>= 1;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read() + 1, k = read();
    init(n);

    for(int i = 0; i < n; i ++ ) F[i] = invfact[i];
    F[0] --;

    lim = 1;
    while(lim < (n << 1)) lim <<= 1, len ++;
    calc();

    ksm(F, G, k);
    for(int i = 0; i < lim; i ++ ) G[i] = G[i] * invfact[k] % mod;

    for(int i = 0; i < n; i ++ ) printf("%lld ", G[i] * fact[i] % mod);

    return 0;
}

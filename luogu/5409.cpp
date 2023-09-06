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

const int N = 1e6 + 10, mod = 167772161;
ll fact[N], invfact[N];
int n, k;
ll F[N], G[N];
int lim = 1, len;
int rev[N];

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

void init(int n)
{
    fact[0] = 1; 
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn = qmi(opt == 1 ? 3 : qmi(3, mod - 2, mod), (mod - 1) / m, mod);
        for(int k = 0; k < lim; k += m)
        {
            ll g = 1;
            for(int j = 0; j < m / 2; j ++ )
            {
                ll u = a[j + k];
                ll t = a[j + k + m / 2] * g % mod;
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

void ksm(ll f[], int k)
{
    G[0] = 1;
    while(k)
    {
        NTT(f, 1);
        if(k & 1)
        {
            NTT(G, 1);
            for(int i = 0; i < lim; i ++ ) G[i] = G[i] * f[i] % mod;
            NTT(G, -1);
            for(int i = n; i < lim; i ++ ) G[i] = 0;
        }
        for(int i = 0; i < lim; i ++ ) f[i] = f[i] * f[i] % mod;
        NTT(f, -1);
        for(int i = n; i < lim; i ++ ) f[i] = 0;
        k >>= 1;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read() + 1, k = read();
    init(n);

    for(int i = 0; i <= n; i ++ ) F[i] = qmi(i, mod - 2, mod);
    while(lim <= n * 2) lim <<= 1, len ++;
    
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    ksm(F, k);

    for(int i = 0; i < n; i ++ ) 
        printf("%lld ", G[i] * invfact[k] % mod * fact[i] % mod);
    
    return 0;
}
#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 1e6 + 10, mod = 1004535809, Gi = 334845270;

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
        x = ((x << 3) + (x << 1) + ch - '0') % mod;
        ch = getchar();
    }
    return x * f;
}

ll F[N], G[N];
int n, k, type;
int rev[N];
int lim, len;

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

inline void calc()
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

inline void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn = qmi(opt == 1 ? 3 : Gi, (mod - 1) / m, mod);
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), type = read();

    for(int i = 0; i < n; i ++ ) F[i] = read();
    
    if(type == 0)
    {
        G[0] = 1;
        for(int i = 1; i < n; i ++ ) G[i] = G[i - 1] * (k + i - 1) % mod * qmi(i, mod - 2, mod) % mod;
    } 
    else
    {
        G[0] = 1;
        for(int i = 1; i < n; i ++ ) G[i] = G[i - 1] * (mod - 1) % mod * (k - i + 1) % mod * qmi(i, mod - 2, mod) % mod; 
    }

    lim = 1, len = 0;
    while(lim <= (n << 1)) lim <<= 1, len ++;
    calc();

    NTT(F, 1), NTT(G, 1);
    for(int i = 0; i < lim; i ++ ) F[i] = F[i] * G[i] % mod;
    NTT(F, -1);

    for(int i = 0; i < n; i ++ ) printf("%lld ", F[i]);
    
    return 0;
}
#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

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

const int N = 1e6 + 10, mod = 1004535809;
ll F[N], G[N];
ll fact[N], invfact[N];
int rev[N];
int lim, len;
int n;

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
        ll gn = qmi(opt == 1 ? 3 : 334845270, (mod - 1) / m, mod);
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

ll h[N];
inline void Inv(ll a[], ll b[], int n)
{
    if(n == 1)
    {
        b[0] = qmi(a[0], mod - 2, mod);
        return;
    }
    Inv(a, b, (n + 1) >> 1);

    lim = 1, len = 0;
    while(lim <= (n << 1)) lim <<= 1, len ++;
    calc();
    
    for(int i = 0; i < lim; i ++ )
        h[i] = i < n ? a[i] : 0;

    NTT(h, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ )
        b[i] = (b[i] * 2 % mod - h[i] * b[i] % mod * b[i] % mod + mod) % mod;
    NTT(b, -1);
    
    for(int i = n; i < lim; i ++ ) b[i] = 0;
}

inline void inte(ll a[], ll b[], int n)
{
    b[0] = 0;
    for(int i = 1; i < n; i ++ ) 
        b[i] = a[i - 1] * qmi(i, mod - 2, mod) % mod;
}

inline void deriva(ll a[], ll b[], int n)
{
    for(int i = 0; i < n - 1; i ++ )
        b[i] = a[i + 1] * (i + 1) % mod;
    b[n - 1] = 0;
}

ll INV[N], LN[N];
inline void ln(ll a[], ll b[], int n)
{
    deriva(a, LN, n);
    Inv(a, INV, n);

    lim = 1, len = 0;
    while(lim <= (n << 1)) lim <<= 1, len ++;
    calc();

    NTT(LN, 1), NTT(INV, 1);
    for(int i = 0; i < lim; i ++ ) LN[i] = LN[i] * INV[i] % mod;
    NTT(LN, -1);

    for(int i = n; i < lim; i ++ ) LN[i] = 0;
    
    inte(LN, b, n);
}

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(n);
    for(int i = 1; i <= n; i ++ ) F[i] = qmi(2, 1ll * i * (i - 1) / 2, mod) * invfact[i] % mod;
    F[0] = 1;
    
    ln(F, G, n + 1);

    // for(int i = 0; i <= n; i ++ ) cout << G[i] * fact[i] % mod << endl;

    cout << G[n] * fact[n] % mod << endl;

    return 0;
}

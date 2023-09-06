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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 998244353;
ll F[N], G[N], H[N];
int rev[N];
int n;
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

inline void calcrev()
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
        ll gn = qmi(opt == 1 ? 3 : 332748118, (mod - 1) / m, mod);
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

inline void inv(ll a[], ll b[], int n)
{
    if(n == 1)
    {
        b[0] = qmi(a[0], mod - 2, mod);
        return;
    }
    inv(a, b, (n + 1) >> 1);
    lim = 1, len = 0;
    while(lim <= n * 2) lim <<= 1, len ++;
    calcrev();
    for(int i = 0; i < lim; i ++ )
    {
        if(i < n) H[i] = a[i];
        else H[i] = 0;
    }
    NTT(H, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ )
        b[i] = (2 * b[i] % mod - H[i] * b[i] % mod * b[i] % mod + mod) % mod;
    NTT(b, -1);
    for(int i = n; i < lim; i ++ ) b[i] = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 0; i < n; i ++ ) F[i] = read();

    inv(F, G, n);

    for(int i = 0; i < n; i ++ ) printf("%lld ", (G[i] % mod + mod) % mod);

    return 0;
}
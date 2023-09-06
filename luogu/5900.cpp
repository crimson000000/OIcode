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

const int N = 1e6 + 10, mod = 998244353;
ll F[N], G[N];
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
    ll up = log2(lim);
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

ll X[N], Y[N];
inline void mul(ll f[], ll g[], int n, int m)
{
    for(int i = 0; i < n; i ++ ) X[i] = f[i];
    for(int i = 0; i < m; i ++ ) Y[i] = g[i];
    for(int i = n; i < lim; i ++ ) X[i] = 0;
    for(int i = m; i < lim; i ++ ) Y[i] = 0;

    NTT(X, 1), NTT(Y, 1);
    for(int i = 0; i < lim; i ++ ) X[i] = X[i] * Y[i] % mod;
    NTT(X, -1);
}

inline void cdq(int l, int r, ll f[], ll g[])
{
    if(r == 1) return;
    if(l == r - 1)
    {
        if(l != 1) f[l] = f[l] * qmi(l - 1, mod - 2, mod) % mod;
        for(int i = l; i < n; i += l) 
            g[i] = (g[i] + f[l] * l % mod) % mod;
        return; 
    }
    int mid = l + r >> 1;
    cdq(l, mid, f, g);
    lim = 1, len = 0;
    while(lim <= r - l) lim <<= 1, len ++;
    calc();

    if(l > 0)
    {
        mul(f, g + l, r - l, mid - l);
        for(int i = mid; i < r; i ++ )
            f[i] = (f[i] + X[i - l]) % mod;
    }
    mul(f + l, g, mid - l, !l ? mid : r - l);
    for(int i = mid; i < r; i ++ ) 
        f[i] = (f[i] + X[i - l]) % mod;
    cdq(mid, r, f, g);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int m = read();
    n = 1;
    while(n <= m) n <<= 1;
    F[1] = 1;

    cdq(0, n, F, G);

    ll ans = F[m];
    for(int i = m / 2 + 1; i <= m - 1; i ++ )
        ans = (ans - F[i] * F[m - i] % mod + mod) % mod;

    if(!(m & 1))
        ans = (ans - F[m / 2] * (F[m / 2] - 1) / 2 % mod + mod) % mod;

    cout << ans << endl;
    
    return 0;
}

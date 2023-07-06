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

const int N = 1e6 + 10, mod = 1004535809, _G = 3, Gi = 334845270, M = 1e7 + 10;
ll n, m, s;
ll w[N], g[N], f[N];
ll F[N], G[N];
int nn;
int fact[M], invfact[M];
int rev[N], lim = 1, len;

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

inline void NTT(ll a[], int lim, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn;
        if(opt == 1) gn = qmi(_G, (mod - 1) / m, mod);
        else gn = qmi(Gi, (mod - 1) / m, mod);
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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = (ll)fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return (ll)fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), s = read();
    init(max(n, m));
    for(int i = 0; i <= m; i ++ ) w[i] = read();

    nn = min(n / s, m);

    for(int i = 0; i <= nn; i ++ )
    {
        g[i] = C(m, i) * fact[n] % mod * invfact[n - i * s] % mod * qmi(invfact[s], i, mod) % mod
                * qmi(m - i, n - i * s, mod) % mod;
    }

    for(int i = 0; i <= nn; i ++ )
    {
        F[i] = invfact[i];
        if(i & 1) F[i] = (mod - F[i]);
        G[i] = (ll)fact[i] * g[i] % mod;
    }

    reverse(G, G + nn + 1);

    while(lim <= (nn << 1)) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    NTT(F, lim, 1), NTT(G, lim, 1);
    for(int i = 0; i < lim; i ++ ) F[i] = F[i] * G[i] % mod;
    NTT(F, lim, -1);

    reverse(F, F + nn + 1);

    ll ans = 0;
    for(int i = 0; i <= nn; i ++ )
        ans = (ans + (ll)w[i] * F[i] % mod * invfact[i] % mod) % mod;

    cout << ans << endl;

    return 0;
}
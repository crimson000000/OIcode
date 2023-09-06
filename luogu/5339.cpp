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

const int N = 1e6 + 10, mod = 998244353, G = 3, Gi = 332748118;
int a, b, c, d, n, sum;
ll g[N];
ll P[N], Q[N], S[N], T[N];
ll fact[N], invfact[N];
ll ans;
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

inline void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn;
        if(opt == 1) gn = qmi(G, (mod - 1) / m, mod);
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

inline ll f(ll n, ll a, ll b, ll c, ll d)
{
    sum = a + b + c + d;
    if(n > sum) return 0;
    if(n < 0) return 0;

    lim = 1, len = 0;
    while(lim < 2 * sum) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    for(int i = 0; i < lim; i ++ ) P[i] = (i <= a) ? invfact[i] : 0;
    for(int i = 0; i < lim; i ++ ) Q[i] = (i <= b) ? invfact[i] : 0;
    for(int i = 0; i < lim; i ++ ) S[i] = (i <= c) ? invfact[i] : 0;
    for(int i = 0; i < lim; i ++ ) T[i] = (i <= d) ? invfact[i] : 0;

    NTT(P, 1), NTT(Q, 1), NTT(S, 1), NTT(T, 1);
    for(int i = 0; i < lim; i ++ ) 
        P[i] = P[i] * Q[i] % mod * S[i] % mod * T[i] % mod;
    NTT(P, -1);
    return P[n] * fact[n] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), a = read(), b = read(), c = read(), d = read();

    sum = a + b + c + d;
    init(sum * 2);
    int minn = min(a, min(b, min(c, d)));

    for(int i = 0; i <= min(n / 4, minn); i ++ ) 
        g[i] = C(n - 3 * i, i) * f(n - 4 * i, a - i, b - i, c - i, d - i) % mod;

    for(int i = 0; i <= min(n / 4, minn); i ++ )
        ans = (ans + ((i & 1) ? mod - 1 : 1) * g[i] % mod + mod) % mod;
    
    cout << ans << endl;

    return 0;
}
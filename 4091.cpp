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
ll n;
ll A[N], B[N];
ll fact[N], invfact[N];
int rev[N];
ll ans;
int lim = 1, len = 0;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(n + 10);

    for(int i = 0; i <= n; i ++ )
    {
        A[i] = ((qmi(i, n + 1, mod) - 1 + mod) % mod * invfact[i] % mod * qmi((i - 1 < 0) ? i + mod - 1 : i - 1, mod - 2, mod) % mod + mod) % mod;
        B[i] = (((i & 1) ? mod - 1 : 1) * invfact[i] % mod + mod) % mod;

        // cout << A[i] << ' ' << B[i] << endl;
    }

    A[1] = n + 1;

    while(lim <= n * 2) lim <<= 1, len ++;
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));

    NTT(A, 1), NTT(B, 1);
    for(int i = 0; i < lim; i ++ ) A[i] = A[i] * B[i] % mod;
    NTT(A, -1);

    // for(int i = 0; i <= n; i ++ )
    // {
    //     for(int j = 0; j <= i; j ++ )
    //         A[i] = (A[i] + ((qmi(j, n + 1, mod) - 1 + mod) % mod * qmi(-1, i - j, mod) % mod + mod) % mod
    //                 * invfact[j] % mod * qmi(j - 1, mod - 2, mod) % mod * invfact[i - j] % mod) % mod;
    //     A[i] = (A[i] % mod + mod) % mod;
    // }

    for(int i = 0; i <= n; i ++ )
    {
    //     cout << A[i] << endl;
        ans = (ans + qmi(2, i, mod) * fact[i] % mod * A[i] % mod + mod) % mod;
        ans = (ans + mod) % mod;
    }

    cout << ans << endl;

    return 0;
}
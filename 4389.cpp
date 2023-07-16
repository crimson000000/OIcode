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
ll a[N], b[N];
ll v[N];
ll inv[N];
int cnt[N];
int rev[N];
int lim, len;
int n, m;

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
        if(rev[i] < i)
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

inline void cdq(int l, int r, ll F[], ll G[])
{
    if(l + 1 == r)
    {
        F[l] = (l ? F[l] * qmi(l, mod - 2, mod) % mod : 1);
        return;
    }
    int mid = l + r >> 1;
    cdq(l, mid, F, G);
    
    lim = 1, len = 0;
    while(lim <= (r - l)) lim <<= 1, len ++;
    calc();

    for(int i = l; i < mid; i ++ ) a[i - l] = F[i];
    for(int i = mid - l; i < lim; i ++ ) a[i] = 0;
    for(int i = 0; i < r - l - 1; i ++ ) b[i] = G[i];
    for(int i = r - l - 1; i < lim; i ++ ) b[i] = 0;

    NTT(a, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
    NTT(a, -1);

    for(int i = mid - l - 1; i < r - l - 1; i ++ )
        F[i + l + 1] = (F[i + l + 1] + a[i]) % mod;
    
    cdq(mid, r, F, G);
}

ll tmp[N];
inline void exp(ll a[], ll b[], int n)
{
    memcpy(tmp, a, n * sizeof(ll));
    for(int i = 1; i < n; i ++ ) tmp[i - 1] = tmp[i] * i % mod;
    tmp[n - 1] = 0;
    cdq(0, n, b, tmp);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) v[i] = read(), cnt[v[i]] ++;

    inv[1] = 1;
    for(int i = 2; i <= m; i ++ )
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;

    for(int i = 1; i <= m; i ++ )
        if(cnt[i])
        {
            for(int j = 1; j <= m / i; j ++ )
                F[i * j] = (F[i * j] + cnt[i] * inv[j] % mod) % mod;
        }

    exp(F, G, m + 1);

    for(int i = 1; i <= m; i ++ ) printf("%lld\n", G[i]);

    return 0;
}

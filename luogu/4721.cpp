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
ll f[N], g[N], a[N], b[N];
int lim, len;
int rev[N];
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

inline void calc_rev(int lim, int len)
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

inline void NTT(ll a[], int lim, int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(rev[i] < i)
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

void cdq(int l, int r)
{
    if(l == r) return;
    if(l >= n) return;
    int mid = l + r >> 1;
    cdq(l, mid);

    int lim = r - l + 1, len = log2(lim);
    calc_rev(lim, len);
    for(int i = l; i <= mid; i ++ ) a[i - l] = f[i];
    for(int i = mid + 1; i <= r; i ++ ) a[i - l] = 0;
    for(int i = 0; i <= r - l + 1; i ++ ) b[i] = g[i];

    NTT(a, lim, 1), NTT(b, lim, 1);
    for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
    NTT(a, lim, -1);

    for(int i = mid + 1; i <= r; i ++ )
        f[i] = (f[i] + a[i - l]) % mod;
    
    cdq(mid + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i < n; i ++ ) g[i] = read();

    f[0] = 1;
    int lg2 = 0;
    while((1 << lg2) < n) lg2 ++;

    cdq(0, (1 << lg2) - 1); 

    for(int i = 0; i < n; i ++ ) printf("%lld ", f[i]);

    return 0;
}

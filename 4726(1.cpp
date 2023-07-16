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

void cdq(int l, int r)
{
    if(l == r - 1)
    {
        if(l) F[l] = F[l] * qmi(l, mod - 2, mod) % mod;
        else F[l] = 1;
        // cout << F[l] << endl;
        return;
    }
    int mid = l + r >> 1;
    cdq(l, mid);

    lim = 1, len = 0;
    while(lim <= (r - l)) lim <<= 1, len ++;
    // cout << lim << ' ' << len << endl;

    for(int i = 0; i < mid - l; i ++ ) a[i] = F[i + l];
    for(int i = mid - l; i < lim; i ++ ) a[i] = 0;
    for(int i = 0; i < r - l - 1; i ++ ) b[i] = G[i];
    for(int i = r - l - 1; i < lim; i ++ ) b[i] = 0;

    calc();
    NTT(a, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
    NTT(a, -1);

    for(int i = mid - l - 1; i < r - l - 1; i ++ ) 
        F[i + l + 1] = (F[i + l + 1] + a[i]) % mod;

    cdq(mid, r);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 0; i < n; i ++ ) G[i] = read();

    for(int i = 1; i < n; i ++ ) G[i - 1] = G[i] * i % mod;
    G[n - 1] = 0;

    // for(int i = 0; i < n; i ++ ) cout << G[i] << ' ';
    // puts("");
    
    cdq(0, n);

    for(int i = 0; i < n; i ++ ) printf("%lld ", F[i]);

    return 0;
}


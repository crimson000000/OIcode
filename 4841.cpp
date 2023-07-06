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

const int N = 1e6 + 10, mod = 1004535809, G = 3;
ll f[N], g[N], a[N], b[N];
int rev[N];
ll fact[N], invfact[N];
int lim, len;
ll n;

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

inline void calcrev() 
{
    for(int i = 0; i < lim; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

inline void NTT(ll a[], int opt)
{
    for(int i = 0; i < lim; i ++ )
        if(rev[i] < i)
            swap(a[rev[i]], a[i]);
    
    int up = log2(lim);
    for(int dep = 1; dep <= up; dep ++ )
    {
        int m = 1 << dep;
        ll gn = qmi(opt == 1 ? G : qmi(G, mod - 2, mod), (mod - 1) / m, mod);
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

void cdq(int l, int r, int log2)
{
    if(log2 <= 0)
    {
        f[l] = (f[l] + qmi(2, l * (l - 1) / 2, mod)) % mod;
        return;
    }
    if(l >= n) return; 
    
    int mid = l + r >> 1;

    cdq(l, mid, log2 - 1);

    lim = 1 << log2, len = log2;
    memset(a + (r - l) / 2, 0, sizeof(ll) * (r - l) / 2);
    memcpy(a, f + l, sizeof(ll) * (r - l) / 2);
    memcpy(b, g, sizeof(ll) * (r - l));

    calcrev();
    NTT(a, 1), NTT(b, 1);
    for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
    NTT(a, -1);

    for(int i = lim / 2; i < lim; i ++ )
        f[i + l] = (f[i + l] - a[i] + mod) % mod;
    
    cdq(mid, r, log2 - 1);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();

    init(n);

    for(int i = 1; i < n; i ++ ) 
    {
        
    }
    
    int log2 = 0;
    while((1 << log2) < n) log2 ++;

    cdq(0, 1 << log2, log2);

    
    // cout << f[n] << endl;

    return 0;
}

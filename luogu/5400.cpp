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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 5e6 + 10, mod = 998244353;
ll n, m, l, k, Y;
ll f[N];
ll a[N], pre[N], inv[N];
ll fact[N], invfact[N];

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

inline ll g(int x)
{
    return (n - x) * (m - x) % mod * (l - x) % mod;
}

inline void getinv(int n)
{
    pre[0] = 1;
    for(int i = 1; i <= n; i ++ ) pre[i] = pre[i - 1] * a[i] % mod;
    inv[n] = qmi(pre[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) inv[i] = inv[i + 1] * a[i + 1] % mod;
    for(int i = 1; i <= n; i ++ ) inv[i] = inv[i] * pre[i - 1] % mod;
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(N - 5);
    while(T -- )
    {
        n = read(), m = read(), l = read(), k = read();
        Y = min({n, m, l});
        for(int i = 1; i <= Y; i ++ )
            a[i] = (n * m % mod * l % mod - g(i) % mod + mod) % mod;
        
        getinv(Y);

        f[0] = 1;
        for(int i = 1; i <= Y; i ++ )
            f[i] = f[i - 1] * (n - i + 1) % mod * (m - i + 1) % mod * (l - i + 1) % mod * inv[i] % mod;
        
        ll ans = 0;
        for(int i = k; i <= Y; i ++ )
        {
            ans = (ans + C(i, k) * f[i] % mod * (((i - k) & 1) ? (mod - 1) : 1) % mod) % mod;
        }

        cout << ans << endl;
    }

    return 0;
}
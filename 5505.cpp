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

const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m;
ll fact[N], invfact[N];
ll a[N];
ll sum, g[N];

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
    return fact[n] * invfact[n - m] % mod * invfact[m] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ ) a[i] = read(), sum = max(sum, a[i]);
    init(sum + n);

    for(int i = 0; i <= n; i ++ )
    {
        g[i] = C(n, i);
        for(int j = 1; j <= m; j ++ )
            g[i] = g[i] * C(a[j] + n - i - 1, n - i - 1) % mod;
    }

    ll ans = 0;
    for(int i = 0; i <= n; i ++ )
        ans = (ans + ((i & 1) ? -1 : 1) * g[i] + mod) % mod;

    cout << ans << endl;

    return 0;
}
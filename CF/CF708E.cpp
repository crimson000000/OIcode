#define LOCAL
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using PII = pair<ll, ll>;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2010, mod = 1e9 + 7, M = 1e5 + 10;
ll s[N], D[N], q[N];
ll fact[M], invfact[M];
ll sumd[N];
ll sl[N][N];
ll p;
int n, m, k;
ll up, down;

inline ll qmi(ll a, ll k, ll p)
{
    if(k < 0) return 0;
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

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    up = read(), down = read();
    p = up * qmi(down, mod - 2, mod) % mod;
    k = read();

    init(k);

    for(int i = 0; i <= m; i ++ )
        D[i] = C(k, i) * qmi(p, i, mod) % mod * qmi(mod + 1 - p, k - i, mod) % mod;

    sumd[0] = D[0];
    for(int i = 1; i <= m; i ++ ) sumd[i] = (sumd[i - 1] + D[i]) % mod;

    sl[0][m] = 1;
    
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ ) s[j] = (s[j - 1] + sl[i - 1][j]) % mod;
        for(int j = 1; j <= m; j ++ ) q[j] = (q[j - 1] + s[j] * D[j]) % mod;
        for(int r = 1; r <= m; r ++ )
            sl[i][r] = D[m - r] * ((s[m] - s[m - r] + mod) % mod * sumd[r - 1] % mod - q[r - 1] + mod) % mod;
    }

    ll ans = 0;
    for(int i = 1; i <= m; i ++ )
        ans = (ans + sl[n][i]) % mod;

    cout << ans << endl;

    return 0;
}

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

const int N = 3010, M = 1e6 + 10, mod = 998244353;
ll fact[M], invfact[M];
ll f[N][N][2], g[N][N][2];
int n, m, k;
int a[N], b[N];
ll ans;

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(10000);

    while(T -- )
    {
        ans = 0;
        n = read(), m = read(), k = read();

        for(int i = 1; i <= n; i ++ ) a[i] = read();
        for(int i = 1; i <= n; i ++ ) b[i] = read();

        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        reverse(a + 1, a + n + 1);
        reverse(b + 1, b + n + 1);
        
        f[0][0][0] = f[0][0][1] = 1;
        for(int i = 1; i <= n; i ++ )
        {
            f[i][0][1] = 1;
            for(int j = 1; j <= i; j ++ )
            {
                f[i][j][0] = f[i - 1][j - 1][1] * (ll)a[i] % mod;
                f[i][j][1] = (f[i][j][0] + f[i - 1][j][1]) % mod;
                g[i][j][0] = ((ll)b[i] * C(i - 1, j - 1) + g[i - 1][j - 1][1]) % mod;
                g[i][j][1] = (g[i][j][0] + g[i - 1][j][1]) % mod;
            }
        }

        for(int i = 0; i < k - 1; i ++ )
        {
            for(int j = 1; j <= n; j ++ )
                ans = (ans + f[n][i][1] * g[j][k - i][0] % mod * C(n - j, m - k) % mod) % mod;
        }

        for(int i = 0; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                ans = (ans + f[i][k - 1][0] * (ll)b[j] % mod * C(2 * n - i - j, m - k) % mod) % mod;

        cout << ans << endl;
    }

    return 0;
}
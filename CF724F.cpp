#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 1010, M = 15;
ll f[N][M][N];
int n, d, mod;
ll inv[N];

inline void init(int n)
{
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; i ++ ) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 1; i <= n; i ++ ) inv[i] = inv[i - 1] * inv[i] % mod;
}

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

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    ll res = 1;
    for(int i = n - m + 1; i <= n; i ++ )
        res = res * i % mod;
    return res * inv[m] % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), d = read(), mod = read();

    init(n);

    if(n == 1 || n == 2)
    {
        puts("1");
        return 0;
    }
    
    for(int i = 0; i <= n; i ++ ) f[1][0][i] = 1;

    f[1][d - 1][0] = 1;
    for(int i = 2; i <= n; i ++ )
        for(int j = 1; j <= min(d, i - 1); j ++ )
            for(int k = 1; k <= n; k ++ )
            {
                f[i][j][k] = f[i][j][k - 1];
                for(int t = 1; t * k <= i && t <= j; t ++ )
                {
                    // if(k > 1)
                    //     f[i][j][k] = (f[i][j][k] + 
                    //         f[i - k * t][j - t][k - 1] * C(f[k][d - 1][k] + t - 1, t) % mod) % mod;
                    // else
                    //     f[i][j][k] = (f[i][j][k] + 
                    //         f[i - k * t][j - t][k - 1] * C(f[k][0][k] + t - 1, t) % mod) % mod;
                    f[i][j][k] = (f[i][j][k] + 
                        f[i - k * t][j - t][k - 1] * C(f[k][d - 1][k - 1] + t - 1, t) % mod) % mod;
                }
            }
    
    ll ans = f[n][d][n / 2];
    if((n & 1) == 0) ans = (ans - C(f[n / 2][d - 1][n / 2 - 1], 2) + mod) % mod;
    cout << ans << endl;

    return 0;
}

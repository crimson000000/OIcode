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

const int N = 2010, mod = 998244353, M = 110;
ll f[N][N], g[M][M * 2];
ll a[N][N], sum[N][N];
int n, m;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            a[i][j] = read();
            sum[i][0] = (sum[i][0] + a[i][j]) % mod;
        }
    
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
        {
            sum[i][j] = (sum[i][0] - a[i][j] + mod) % mod;
            // cout << sum[i][j] << ' ';
        }
        // puts("");
    }
    
    f[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        f[i][0] = f[i - 1][0];
        for(int j = 1; j <= n; j ++ )
            f[i][j] = (f[i - 1][j] + sum[i][0] * f[i - 1][j - 1] % mod) % mod;
    }

    for(int i = 1; i <= n; i ++ ) ans = (ans + f[n][i]) % mod;

    for(int p = 1; p <= m; p ++ )
    {
        memset(g, 0, sizeof g);
        g[0][n] = 1;
        for(int i = 1; i <= n; i ++ )
        {
            for(int j = n - i; j <= n + i; j ++ )
            {
                g[i][j] = (g[i - 1][j] + a[i][p] * g[i - 1][j - 1] % mod + sum[i][p] * g[i - 1][j + 1] % mod) % mod;
            }
        }

        for(int j = 1; j <= n; j ++ )
        {
            // cout << g[n][n + j] << endl;
            ans = (ans - g[n][n + j] + mod) % mod;
        }
    }

    cout << (ans % mod + mod) % mod << endl;

    return 0;
}

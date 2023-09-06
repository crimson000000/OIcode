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

const int N = 110, M = 12, mod = 998244353;
ll f[N][N][1 << M];
ll fact[N], invfact[N];
int n, m;
ll ans;

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
} 

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read() - 1;
    init(n);

    f[0][0][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j < i; j ++ )
        {
            for(int s = 0; s < (1 << (m * 2 + 1)); s ++ )
            {
                if(!f[i - 1][j][s]) continue;
                int T = s >> 1;
                f[i][j][T] = (f[i][j][T] + f[i - 1][j][s]) % mod;
                for(int k = 0; k < (2 * m + 1); k ++ )
                {
                    if(T >> k & 1) continue;
                    if(i + k - m < 1 || i + k - m > n) continue;
                    f[i][j + 1][T | (1 << k)] = (f[i][j + 1][T | (1 << k)] + f[i - 1][j][s]) % mod;
                }
            }
        }

    for(int i = 0; i <= n; i ++ )
    {
        for(int s = 0; s < (1 << (2 * m + 1)); s ++ )
        {
            ll t = (i & 1) ? (mod - f[n][i][s]) : f[n][i][s];
            ans = (ans + fact[n - i] * t % mod) % mod;
        }
    }

    cout << ans << endl;

    return 0;
}
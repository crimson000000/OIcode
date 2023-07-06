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

const int N = 1e5 + 10;
ll n, k;
ll f[50][N], g[50][N], h[50][N];

ll minn, sum;
inline void calc(int s)
{
    minn = 1e17, sum = 0;
    int p = s;
    ll t = k;
    for(int i = 49; i >= 0; i -- )
    {
        if((1ll << i) <= t)
        {
            minn = min(minn, h[i][p]);
            sum += g[i][p];
            t -= (1ll << i);
            p = f[i][p];
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) f[0][i] = read() + 1;
    for(int i = 1; i <= n; i ++ ) g[0][i] = read(), h[0][i] = g[0][i];
    
    for(int i = 1; i <= 49; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            f[i][j] = f[i - 1][f[i - 1][j]];
            g[i][j] = g[i - 1][j] + g[i - 1][f[i - 1][j]];
            h[i][j] = min(h[i - 1][j], h[i - 1][f[i - 1][j]]);
        }

    for(int i = 1; i <= n; i ++ )
    {
        calc(i);
        printf("%lld %lld\n", sum, minn);
    }

    return 0;
}

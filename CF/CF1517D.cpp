#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 510;
ll f[15][N][N];
int n, m, k;
int dow[N][N], rig[N][N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    if(k & 1)
    {
        for(int i = 1; i <= n; i ++ )
        {
            for(int j = 1; j <= m; j ++ )
                printf("-1 ");
            puts("");
        }

        return 0;
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j < m; j ++ )
            rig[i][j] = read();
    
    for(int i = 1; i < n; i ++ )
        for(int j = 1; j <= m; j ++ )
            dow[i][j] = read();
    
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            f[0][i][j] = 0;
    
    for(int s = 1; s <= k / 2; s ++ )
    {
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= m; j ++ )
            {
                if(i + 1 <= n) f[s][i][j] = min(f[s][i][j], f[s - 1][i + 1][j] + dow[i][j]);
                if(i - 1 > 0) f[s][i][j] = min(f[s][i][j], f[s - 1][i - 1][j] + dow[i - 1][j]);
                if(j - 1 > 0) f[s][i][j] = min(f[s][i][j], f[s - 1][i][j - 1] + rig[i][j - 1]);
                if(j + 1 <= m) f[s][i][j] = min(f[s][i][j], f[s - 1][i][j + 1] + rig[i][j]);
            }
    }

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
            printf("%lld ", f[k / 2][i][j] * 2);
        puts("");
    }

    return 0;
}
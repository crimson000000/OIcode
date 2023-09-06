#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 55, M = 2510;
int f[N][M], g[N][M][N];
int sum[N][N];
char s[N][N];
int n, m, t;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d%d", &n, &m, &t);
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", s[i] + 1);
        for(int j = 1; j <= m; j ++ )
        {
            if(s[i][j] == '1') sum[i][j] = sum[i][j - 1] + 1;
            else sum[i][j] = sum[i][j - 1];
        }
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            for(int k = 1; k <= m; k ++ )
                for(int u = j - 1; u < k; u ++ )
                    g[i][j][k] = max(g[i][j][k], g[i][j - 1][u] + max(sum[i][k] - sum[i][u], k - u - (sum[i][k] - sum[i][u])));
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= t; j ++ )
            for(int k = 1; k <= min(j, m); k ++ )
                f[i][j] = max(f[i][j], f[i - 1][j - k] + g[i][k][m]);

    int ans = 0;
    for(int i = 1; i <= t; i ++ ) ans = max(ans, f[n][i]);
    cout << ans << endl;

    return 0;
}

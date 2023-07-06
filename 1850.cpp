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

const int N = 2010;
double f[N][N][2], p[N];
int dist[N][N], c[N], d[N];
int n, m, v, e;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), v = read(), e = read();

    memset(dist, 0x3f, sizeof dist);
    for(int i = 1; i <= v; i ++ ) dist[i][i] = 0;
    for(int i = 1; i <= n; i ++ ) c[i] = read();
    for(int i = 1; i <= n; i ++ ) d[i] = read();
    for(int i = 1; i <= n; i ++ ) cin >> p[i];
    while(e -- )
    {
        int a = read(), b = read(), c = read();
        dist[a][b] = dist[b][a] = min(dist[a][b], c);
    }

    for(int k = 1; k <= v; k ++ )
        for(int i = 1; i <= v; i ++ )
            for(int j = 1; j <= v; j ++ )
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // for(int i = 1; i <= v; i ++ )
    // {
    //     for(int j = 1; j <= v; j ++ )
    //         cout << dist[i][j] << ' ';
    //     puts("");
    // }
    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j <= m; j ++ )
            f[i][j][0] = f[i][j][1] = 1e20;

    f[1][0][0] = f[1][1][1] = 0;

    for(int i = 2; i <= n; i ++ )
        for(int j = 0; j <= min(i, m); j ++ )
        {
            f[i][j][0] = min(f[i][j][0], f[i - 1][j][0] + (double)dist[c[i - 1]][c[i]]);
            f[i][j][0] = min(f[i][j][0], 
                        f[i - 1][j][1] + (double)dist[d[i - 1]][c[i]] * p[i - 1] + 
                        (double)dist[c[i - 1]][c[i]] * (1 - p[i - 1]));

            if(j != 0)
            {
                f[i][j][1] = min(f[i][j][1], 
                            f[i - 1][j - 1][0] + (double)dist[c[i - 1]][d[i]] * p[i] + 
                            (double)dist[c[i - 1]][c[i]] * (1 - p[i]));
                f[i][j][1] = min(f[i][j][1], f[i - 1][j - 1][1] + 
                            (double)dist[c[i - 1]][c[i]] * (1 - p[i]) * (1 - p[i - 1]) + 
                            (double)dist[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] + 
                            (double)dist[d[i - 1]][c[i]] * p[i - 1] * (1 - p[i]) + 
                            (double)dist[d[i - 1]][d[i]] * p[i - 1] * p[i]);
            }
        }

    double ans = 1e9;
    for(int i = 0; i <= m; i ++ ) 
    {
        // cout << f[n][i][0] << ' ' << f[n][i][1] << endl;
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    }

    printf("%.2lf\n", ans);
    
    return 0;
}

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

const int N = 110;
int d[N][N], f[N][N];
int n, m;
int s, t;
int X[N], Y[N], cnt;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            d[i][j] = read();

    for(int i = 0; i <= 100; i ++ )
        for(int j = 0; j <= 100; j ++ )
            for(int x = 1; x <= n; x ++ )   
                for(int y = 1; y <= m; y ++ )
                    f[i][j] = max(f[i][j], d[x][y] - i * x - j * y);

    for(int x = 1; x <= n; x ++ )   
        for(int y = 1; y <= m; y ++ )
        {
            int now = 0x3f3f3f3f;
            for(int i = 0; i <= 100; i ++ )
                for(int j = 0; j <= 100; j ++ )
                    now = min(now, i * x + j * y + f[i][j]);
            if(d[x][y] != now) 
            {
                puts("Impossible");
                return 0;
            }
        }

    puts("Possible");
    printf("%d %d\n", 202, 10401);

    for(int i = 1; i <= 100; i ++ )
        printf("%d %d X\n", i, i + 1);
    
    for(int i = 102; i < 202; i ++ )
        printf("%d %d Y\n", i, i + 1);
    
    for(int i = 0; i <= 100; i ++ )
        for(int j = 0; j <= 100; j ++ )
            printf("%d %d %d\n", 1 + i, 202 - j, f[i][j]);
    
    puts("1 202");

    return 0;
}
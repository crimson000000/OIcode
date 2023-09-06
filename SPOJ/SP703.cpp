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

const int N = 1010, M = 210;
int f[N][M][M];
int c[N][N];
int pos[N];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T;
    scanf("%d", &T);
    while(T -- )
    {
        scanf("%d%d", &n, &m);

        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                scanf("%d", &c[i][j]);

        for(int i = 1; i <= m; i ++ )
            scanf("%d", &pos[i]);

        memset(f, 0x3f, sizeof f);
        
        f[0][1][2] = 0;
        pos[0] = 3;
        for(int i = 0; i < m; i ++ )
            for(int j = 1; j <= n; j ++ )
                for(int k = 1; k <= n; k ++ )
                {
                    if(j == pos[i] || k == pos[i] || k == j) continue;
                    
                    f[i + 1][j][pos[i]] = min(f[i + 1][j][pos[i]], f[i][j][k] + c[k][pos[i + 1]]);
                    f[i + 1][pos[i]][k] = min(f[i + 1][pos[i]][k], f[i][j][k] + c[j][pos[i + 1]]);
                    f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + c[pos[i]][pos[i + 1]]);
                }

        int ans = 0x3f3f3f3f;
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
                ans = min(ans, f[m][i][j]);

        cout << ans << endl;
    }
    
    return 0;
}

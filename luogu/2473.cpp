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

const int N = 110, M = 1 << 15;
double f[N][M];
int k, n;
int need[N];
int p[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    k = read(), n = read();
    for(int i = 1; i <= n; i ++ )
    {
        p[i] = read();
        int x;
        while(x = read()) need[i] |= (1 << x - 1);
    }

    for(int i = k; i; i -- )
        for(int j = 0; j < 1 << n; j ++ )
        {
            for(int u = 1; u <= n; u ++ )
            {
                if(((need[u] | j) == j))
                    f[i][j] += max(f[i + 1][j], f[i + 1][j | (1 << u - 1)] + (double)p[u]);
                else f[i][j] += f[i + 1][j];
            }
            f[i][j] /= n;
        }

    printf("%.6lf\n", f[1][0]);
    
    return 0;
}

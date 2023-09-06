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

const int N = 45;
int f[N][N][N][N];
int a[5];
int w[1010];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ )
        scanf("%d", &w[i]);

    for(int i = 1; i <= m; i ++ )
    {
        int t;
        scanf("%d", &t);
        a[t] ++;
    }

    f[0][0][0][0] = w[1];
    for(int i = 0; i <= a[1]; i ++ )
        for(int j = 0; j <= a[2]; j ++ )
            for(int k = 0; k <= a[3]; k ++ )
                for(int u = 0; u <= a[4]; u ++ )
                {
                    int r = 1 + i + 2 * j + 3 * k + 4 * u;
                    int &v = f[i][j][k][u];
                    if(i != 0) v = max(v, f[i - 1][j][k][u] + w[r]);
                    if(j != 0) v = max(v, f[i][j - 1][k][u] + w[r]);
                    if(k != 0) v = max(v, f[i][j][k - 1][u] + w[r]);
                    if(u != 0) v = max(v, f[i][j][k][u - 1] + w[r]);
                }

    cout << f[a[1]][a[2]][a[3]][a[4]] << endl;

    return 0;
}

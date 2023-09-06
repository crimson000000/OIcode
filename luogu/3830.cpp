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

const int N = 110;
double f[N][N];
double f1[N];
int q, n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> q >> n;
    if(q == 1)
    {
        for(int i = 2; i <= n; i ++ )
            f1[i] = f1[i - 1] + 2.0 / i;
        printf("%.6lf\n", f1[n]);
    }
    else
    {
        for(int i = 1; i <= n; i ++ ) f[i][0] = 1;
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j < i; j ++ )
            {
                for(int k = 1; k <= i - 1; k ++ )
                    f[i][j] += f[k][j - 1] + f[i - k][j - 1] - f[k][j - 1] * f[i - k][j - 1];
                f[i][j] /= (i - 1);
            }
        double ans = 0;
        for(int i = 1; i <= n; i ++ )
            ans += f[n][i];
        printf("%.6lf\n", ans);
    }

    return 0;
}

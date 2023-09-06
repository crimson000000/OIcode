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
double a[N][N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n + 1; j ++ )
            cin >> a[i][j];
    
    for(int i = 1; i <= n; i ++ )
    {
        int pos = i;
        for(int j = i; j <= n; j ++ )
            if(fabs(a[j][i]) > fabs(a[pos][i]))
                pos = j;
        for(int j = i; j <= n + 1; j ++ )
            swap(a[pos][j], a[i][j]);

        if(fabs(a[i][i]) < 1e-6 && fabs(a[i][n + 1]) < 1e-6 ) 
        {
            puts("infinity Solution");
            return 0;
        }
        else if(fabs(a[i][i]) < 1e-6)
        {
            puts("no solution");
            return 0;
        }

        for(int j = 1; j <= n; j ++ )
            if(j != i)
            {
                double tmp = a[j][i] / a[i][i];
                for(int k = 1; k <= n + 1; k ++ )
                    a[j][k] -= tmp * a[i][k];
            }
    }

    for(int i = 1; i <= n; i ++ )
        printf("%.2lf\n", a[i][n + 1] / a[i][i]);

    return 0;
}

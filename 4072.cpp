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

const int N = 3010;
double f[N][N], _x;
int n, m;
int q[N], hh, tt;
ll a[N], s[N];

inline double Y(int i, int x)
{
    return f[i - 1][x] + s[x] * s[x];
}

inline double K(int x)
{
    return 2 * (s[x] - _x);
}

inline ll X(int x)
{
    return s[x];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        s[i] = s[i - 1] + a[i];
    }

    _x = (double)s[n] / m;

    for(int i = 0; i <= m; i ++ )
        for(int j = 0; j <= n; j ++ )
            f[i][j] = 1e20;

    f[0][0] = 0;
    for(int i = 1; i <= m; i ++ )
    {
        hh = 0, tt = 0;
        for(int j = 1; j <= n; j ++ )
        {
            while(hh < tt && (Y(i, q[hh + 1]) - Y(i, q[hh])) <= K(j) * (X(q[hh + 1]) - X(q[hh])))
                hh ++;
            f[i][j] = f[i - 1][q[hh]] + (s[j] - s[q[hh]] - _x) * (s[j] - s[q[hh]] - _x);
            while(hh < tt && (Y(i, q[tt]) - Y(i, q[tt - 1])) * (X(j) - X(q[tt])) >= 
                            (Y(i, j) - Y(i, q[tt])) * (X(q[tt]) - X(q[tt - 1])))
                tt --;
            q[++ tt] = j;
        }
    }
    
    printf("%.0lf\n", f[m][n] * m);

    return 0;
}
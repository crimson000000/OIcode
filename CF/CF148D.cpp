#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
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

const int N = 1010;
ld f[N][N][2];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 0; j <= m; j ++ )
        {
            ld a = i, b = j;
            f[i][j][0] += a / (a + b);
            if(j >= 1) f[i][j][0] += b / (a + b) * f[i][j - 1][1];
            if(i >= 1 && j >= 1) f[i][j][1] += b / (a + b) * a / (a + b - 1) * f[i - 1][j - 1][0];
            if(j >= 2) f[i][j][1] += b / (a + b) * (b - 1) / (a + b - 1) * f[i][j - 2][0];
        }
    }

    printf("%.12Lf\n", f[n][m][0]);

    return 0;
}
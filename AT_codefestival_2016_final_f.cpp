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

const int N = 310, mod = 1e9 + 7;
ll f[N][N][N];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    f[0][1][1] = 1;
    for(int i = 0; i < m; i ++ )
        for(int j = 1; j <= n; j ++ )
            for(int k = 1; k <= j; k ++ )
            {
                (f[i + 1][j + 1][k] += f[i][j][k] * (n - j)) %= mod;
                (f[i + 1][j][k] += f[i][j][k] * (j - k)) %= mod;
                (f[i + 1][j][j] += f[i][j][k] * k) %= mod;
            }

    cout << f[m][n][n] << endl;

    return 0;
}
#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

const int N = 3010;
int f[N][N];
int s[N];
int d[N][N];
int X[N];
int n, m;

int calc(int l, int r)
{
    int mid = l + r + 1 >> 1;
    return X[mid] * (mid - l + 1) - (s[mid] - s[l - 1]) + (s[r] - s[mid]) - X[mid] * (r - mid);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) X[i] = read();

    sort(X + 1, X + n + 1);
    for(int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + X[i];

    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; i ++ ) f[i][1] = calc(1, i);
    for(int i = 1; i <= m; i ++ ) d[n][i] = 1;
    for(int j = 2; j <= m; j ++ )
    {
        d[n + 1][j] = n;
        for(int i = n; i; i -- )
        {
            int minid = -1;
            for(int k = d[i][j - 1]; k <= d[i + 1][j]; k ++ )
                if(f[k][j - 1] + calc(k + 1, i) < f[i][j])
                {
                    f[i][j] = f[k][j - 1] + calc(k + 1, i);
                    minid = k;
                }
            d[i][j] = minid;
        }
    }

    cout << f[n][m] << endl;

    return 0;
}
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

const int N = 5010, mod = 1e9 + 7;
int f[N][N];
int n, m;
char s[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);
    m = strlen(s + 1);

    f[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 0; j <= i; j ++ )
        {
            f[i][j] = (f[i - 1][max(j - 1, 0)] + f[i - 1][j + 1] * 2ll) % mod;
        }
    }

    cout << f[n][m] << endl;

    return 0;
}
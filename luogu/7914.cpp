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

const int N = 510, mod = 1e9 + 7;
ll f[N][N][6];
char s[N];
int n, k;

inline bool cmp(int l, int r)
{
    return (s[l] == '(' || s[l] == '?') && (s[r] == ')' || s[r] == '?');
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    scanf("%s", s + 1);
    
    for(int i = 1; i <= n; i ++ ) f[i][i - 1][0] = 1;

    for(int len = 1; len <= n; len ++ )
        for(int l = 1; l <= n; l ++ )
        {
            int r = l + len - 1;
            if(r > n) break;
            if(len <= k) f[l][r][0] = f[l][r - 1][0] & (s[r] == '*' || s[r] == '?');
            if(len >= 2) 
            {
                if(cmp(l, r))
                    f[l][r][1] = (f[l + 1][r - 1][0] + f[l + 1][r - 1][2] + f[l + 1][r - 1][3] + f[l + 1][r - 1][4]) % mod;
                for(int k = l; k < r; k ++ )
                {
                    f[l][r][2] = (f[l][r][2] + f[l][k][3] * f[k + 1][r][0]) % mod;
                    f[l][r][3] = (f[l][r][3] + (f[l][k][2] + f[l][k][3]) % mod * f[k + 1][r][1]) % mod;
                    f[l][r][4] = (f[l][r][4] + (f[l][k][4] + f[l][k][5]) % mod * f[k + 1][r][1]) % mod;
                    f[l][r][5] = (f[l][r][5] + f[l][k][4] * f[k + 1][r][0]) % mod;
                }
            }

            f[l][r][3] = (f[l][r][3] + f[l][r][1]) % mod;
            f[l][r][5] = (f[l][r][5] + f[l][r][0]) % mod;
        } 

    cout << f[1][n][3] << endl;

    return 0;
}
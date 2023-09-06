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

const int N = 1010, S = 1 << 15, mod = 1e9 + 7;
char a[N];
int dp[2][S][3];
int siz[S];
int ans[N];
int now, lst;
int n, m;

inline ll Hash(int a[])
{
    int res = 0;
    for(int i = 0; i < m; i ++ ) 
        res |= (a[i + 1] - a[i]) << i;
    return res;
}

inline void Unzip(int x, int a[])
{
    for(int i = 0; i < m; i ++ ) a[i + 1] = (x >> i) & 1;
    for(int i = 1; i <= m; i ++ ) a[i] += a[i - 1];
}

int f1[N], f2[N];
inline void trans(int state, char ch, int K, int v)
{
    Unzip(state, f1);
    for(int i = 1; i <= m; i ++ )
        f2[i] = max({f2[i - 1], f1[i], f1[i - 1] + (a[i] == ch)});
    int nstate = Hash(f2);
    dp[now][nstate][K] = (dp[now][nstate][K] + v) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    scanf("%s", a + 1);
    
    for(int i = 1; i < (1 << m); i ++ )
        siz[i] = siz[i - (i & -i)] + 1;

    now = 0, lst = 1;
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        swap(now, lst);
        for(int j = 0; j < (1 << m); j ++ )
            for(int k = 0; k < 3; k ++ )
                dp[now][j][k] = 0;
        
        for(int j = 0; j < (1 << m); j ++ )
        {
            if(dp[lst][j][0] != 0)
            {
                trans(j, 'N', 1, dp[lst][j][0]);
                trans(j, 'O', 0, dp[lst][j][0]);
                trans(j, 'I', 0, dp[lst][j][0]);
            }
            if(dp[lst][j][1] != 0)
            {
                trans(j, 'N', 1, dp[lst][j][1]);
                trans(j, 'O', 2, dp[lst][j][1]);
                trans(j, 'I', 0, dp[lst][j][1]);
            }
            if(dp[lst][j][2] != 0)
            {
                trans(j, 'N', 1, dp[lst][j][2]);
                trans(j, 'O', 0, dp[lst][j][2]);
            }
        }
    }

    for(int i = 0; i < (1 << m); i ++ )
        for(int j = 0; j < 3; j ++ )
            ans[siz[i]] = (ans[siz[i]] + dp[now][i][j]) % mod;
    
    for(int i = 0; i <= m; i ++ )
        printf("%d\n", ans[i]);

    return 0;
}
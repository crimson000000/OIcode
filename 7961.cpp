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

const int mod = 998244353, N = 110;
ll dp[105][35][35][35];
ll v[50], pv[N][N];
ll C[N][N];
int n, m, K;

inline void init(int n)
{
    for(int i = 0; i <= n; i ++ ) C[i][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

inline int popcount(int x)
{
    int cnt = 0;
    while(x) 
    {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), K = read();
    init(30);

    for(int i = 0; i <= m; i ++ )
    {
        v[i] = read();
        pv[i][0] = 1;
        for(int j = 1; j <= n; j ++ ) pv[i][j] = pv[i][j - 1] * v[i] % mod;
    } 

    dp[0][0][0][0] = 1;
    for(int i = 0; i <= m; i ++ )
        for(int j = 0; j <= n; j ++ )
            for(int k = 0; k <= K; k ++ )
                for(int p = 0; p <= (n >> 1); p ++ )
                    for(int t = 0; t <= n - j; t ++ )
                        dp[i + 1][j + t][k + (t + p & 1)][(t + p) >> 1] = 
                        (dp[i + 1][j + t][k + (t + p & 1)][(t + p) >> 1] + 
                         dp[i][j][k][p] * pv[i][t] % mod * C[n - j][t] % mod) % mod;

    ll ans = 0;
    for(int i = 0; i <= K; i ++ )
        for(int p = 0; p <= (n >> 1); p ++ )
            if(i + popcount(p) <= K)
                ans = (ans + dp[m + 1][n][i][p]) % mod;
    
    cout << ans % mod << endl;

    return 0;
}
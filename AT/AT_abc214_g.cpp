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

const int mod = 1e9 + 7, N = 3010;
ll f[N][N], g[N][N], dp[N][N], h[N];
ll fact[N];
ll p[N], q[N];
ll ne[N], la[N];
bitset<N> vis;
vector<int> d;
ll n, ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    fact[0] = 1;
    for(int i = 1; i <= n + 1; i ++ ) 
    {
        fact[i] = fact[i - 1] * i % mod;
        dp[1][i] = i;
    }

    for(int i = 2; i <= n + 1; i ++ )
    {
        ll sum1 = 0, sum2 = 0;
        sum1 = sum2 = dp[i - 1][i - 1];
        for(int j = i; j <= n + 1; j ++ )
        {
            dp[i][j] = sum2;
            sum1 = (sum1 + dp[i - 1][j]) % mod;
            sum2 = (sum2 + sum1) % mod;
        }
    }

    for(int i = 1; i <= n + 1; i ++ )
    {
        f[1][i] = i * i % mod;
        f[0][i] = 2;
    }

    for(int i = 2; i <= n + 1; i ++ )
    {
        ll sum1 = dp[i - 1][i - 1];
        ll sum2 = dp[i - 1][i - 1];
        ll sum3 = dp[i - 1][i - 1];
        for(int j = i; j <= n + 1; j ++ )
        {
            f[i][j] = sum3;
            sum2 = (sum2 + sum1 * 2) % mod;
            sum1 = (sum1 + dp[i - 1][j]) % mod;
            sum2 = (sum2 + dp[i - 1][j]) % mod;
            sum3 = (sum3 + sum2) % mod;
        }
    }

    for(int i = 1; i <= n; i ++ ) p[i] = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        q[i] = read();
        ne[p[i]] = q[i];
        la[q[i]] = p[i];
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(!vis[p[i]])
        {
            int num = 1;
            int st = p[i];
            vis[st] = true;
            while(ne[st] != p[i])
            {
                st = ne[st];
                num ++;
                vis[st] = true;
            }
            d.push_back(num);
        }
    }

    ll sum = 0;
    for(int i = 0; i < d.size(); i ++ )
    {
        ll v = d[i];
        sum += v;
        if(i == 0)
        {
            if(v == 1)
            {
                g[i][0] = 1;
                g[i][1] = 1;
                continue;
            }
            g[i][0] = 2;
            for(int j = 1; j <= v; j ++ )
                g[i][j] = f[j][v];
            continue;
        }
        if(v == 1)
        {
            for(int j = 0; j <= sum; j ++ )
            {
                g[i][j] = g[i - 1][j];
                if(j) g[i][j] = (g[i][j] + g[i - 1][j - 1]) % mod;
            }
            continue;
        }
        for(int j = 0; j <= sum; j ++ )
            for(int k = max(j - v, 0ll); k <= sum - v; k ++ )
                g[i][j] = (g[i][j] + g[i - 1][k] * f[j - k][v] % mod) % mod;
    }

    for(int i = 0; i <= n; i ++ )
        h[n - i] = g[d.size() - 1][i];

    for(int i = 0; i <= n; i ++ )
    {
        if(i & 1) ans = (ans - h[i] * fact[n - i] % mod + mod) % mod;
        else ans = (ans + h[i] * fact[n - i] % mod) % mod;
    }
    
    cout << ans << endl;

    return 0;
}

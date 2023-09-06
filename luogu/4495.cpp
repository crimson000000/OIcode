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

const int N = 1e6 + 10, M = 2010, mod = 1e9 + 7;
int v[N], cnt[N], g[N];
unordered_map<int, int> id;
int n, q, p, m;
int pow2[N];
int tot;
int f[M][M], ans[N];

inline int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

inline void divide(int x)
{
    for(int i = 1; i <= x / i; i ++ )
    {
        if(x % i == 0)
        {
            g[++ m] = i;
            // id[i] = m;
            if(i * i != x) 
            {
                g[++ m] = x / i;
                // id[x / i] = m;
            }
        }
    }

    sort(g + 1, g + m + 1);
    for(int i = 1; i <= m; i ++ ) id[g[i]] = i;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), q = read(), p = read();

    divide(p);

    for(int i = 1; i <= n; i ++ ) v[i] = gcd(p, read());

    sort(v + 1, v + n + 1);

    for(int i = 1; i <= n; i ++ )
        if(v[i] != v[i - 1]) 
        {
            v[++ tot] = v[i];
            cnt[tot] = 1;
        }
        else cnt[tot] ++;

    pow2[0] = 1;
    for(int i = 1; i <= n; i ++ ) pow2[i] = (ll)pow2[i - 1] * 2 % mod;

    f[0][m] = 1;
    for(int i = 1; i <= tot; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            int k = id[gcd(g[j], v[i])];
            f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            f[i][k] = (f[i][k] + (ll)f[i - 1][j] * (pow2[cnt[i]] - 1)) % mod;
        }

    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= i; j ++ )
            if(g[i] % g[j] == 0)
                ans[i] = (ans[i] + f[tot][j]) % mod;
    
    while(q -- )
    {
        int x = read();
        x = id[gcd(x, p)];
        printf("%d\n", ans[x]);
    }

    return 0;
}

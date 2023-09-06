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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 20;
int d[N][N];
ll f[N][N];
int n, m;
int h[N], e[N << 5], ne[N << 5], idx;
ll ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void dfs(int u, int fa, int s)
{
    for(int i = 1; i <= n; i ++ )
        if(s >> (i - 1) & 1)
            f[u][i] = 1;
        else f[u][i] = 0;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u, s);
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(!(s >> (i - 1) & 1)) continue;
        for(int _ = h[u]; _ != -1; _ = ne[_])
        {
            int v = e[_];
            if(v == fa) continue;
            ll sum = 0;
            for(int j = 1; j <= n; j ++ )
            {
                if(!(s >> (j - 1) & 1)) continue;
                if(!d[i][j]) continue;
                sum += f[v][j];
            }
            f[u][i] *= sum;
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        d[a][b] = 1;
        d[b][a] = 1;
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }

    for(int i = 1; i < (1 << n); i ++ )
    {
        int cnt = 0;
        for(int j = 0; j < n; j ++ )
            if(i >> j & 1)
                cnt ++;
        dfs(1, 0, i);
        ll res = 0;
        for(int j = 1; j <= n; j ++ )
            res += f[1][j];
        ans = ans + (((n - cnt) & 1) ? -1 : 1) * res; 
    }

    cout << ans << endl;

    return 0;
}
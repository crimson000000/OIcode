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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1010;
ld f[N], g[N], h[N];
ld p[N][N];
int n;
int q[N], tt;
bitset<N> vis;

inline void update()
{
    int v = q[tt];
    for(int u = 1; u <= n; u ++ )
    {
        if(vis[u]) continue;
        g[u] += f[v] * h[u] * p[u][v];
        h[u] *= 1 - p[u][v];
        f[u] = g[u] / (1 - h[u]);
    }
}

inline void dijkstra()
{
    for(int i = 1; i < n; i ++ )
        f[i] = g[i] = h[i] = 1;
    f[n] = 0, h[n] = 1;
    vis[n] = true;
    q[++ tt] = n;
    update();
    while(tt < n)
    {
        int id = 0;
        ld v = 1e20;
        for(int i = 1; i <= n; i ++ )
        {
            if(vis[i]) continue;
            if(f[i] < v)
                v = f[i], id = i;
        }
        vis[id] = true;
        q[++ tt] = id;
        update();
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            int x = read();
            p[i][j] = x / 100.0;
        }

    dijkstra();

    printf("%.10Lf\n", f[1]);

    return 0;
}

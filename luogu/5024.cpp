#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int ll

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

const int N = 1e6 + 10, INF = 1e18;
int f[N][2], g[N][2], fh[N >> 1][20][2][2];
int h[N], e[N], ne[N], idx;
int w[N];
int n, m;
char ccfnmsl[5];
map<PII, bool> mp;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dep[N], fa[N >> 1][20];
void dp1(int u, int father)
{
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    f[u][1] = w[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;
        dp1(j, u);
        f[u][1] += min(f[j][0], f[j][1]);
        f[u][0] += f[j][1];
    }
}

void dp2(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u][0]) continue;
        g[v][0] = g[u][1] + f[u][1] - min(f[v][1], f[v][0]);
        g[v][1] = min(g[u][0] + f[u][0] - f[v][1], g[v][0]);
        dp2(v);
    }
}

inline int solve(int x, int a, int y, int b)
{
    if(dep[x] < dep[y]) swap(x, y), swap(a, b);
    int tx[2] = {INF, INF}, ty[2] = {INF, INF};
    int nx[2], ny[2];
    tx[a] = f[x][a], ty[b] = f[y][b];
    for(int i = 18; i >= 0; i -- )
    {
        if(dep[fa[x][i]] >= dep[y])
        {
            nx[0] = nx[1] = INF;
            for(int u = 0; u < 2; u ++ )
                for(int v = 0; v < 2; v ++ )
                    nx[u] = min(nx[u], tx[v] + fh[x][i][v][u]);
            tx[0] = nx[0], tx[1] = nx[1];
            x = fa[x][i];
        }
    }
    
    if(x == y) return tx[b] + g[x][b];

    for(int i = 18; i >= 0; i -- )
    {
        if(fa[x][i] != fa[y][i])
        {
            nx[0] = nx[1] = ny[0] = ny[1] = INF;
            for(int u = 0; u < 2; u ++ )
                for(int v = 0; v < 2; v ++ )
                {
                    nx[u] = min(nx[u], tx[v] + fh[x][i][v][u]);
                    ny[u] = min(ny[u], ty[v] + fh[y][i][v][u]);
                }
            tx[0] = nx[0], tx[1] = nx[1];
            ty[0] = ny[0], ty[1] = ny[1];
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    int lca = fa[x][0];
    int ans0 = f[lca][0] - f[x][1] - f[y][1] + tx[1] + ty[1] + g[lca][0];
    int ans1 = f[lca][1] - min(f[x][1], f[x][0]) - min(f[y][0], f[y][1]) + min(tx[0], tx[1])
                + min(ty[0], ty[1]) + g[lca][1];
    return min(ans0, ans1);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    scanf("%s", ccfnmsl);

    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        mp[{a, b}] = true;
        mp[{b, a}] = true;
    }

    dp1(1, 0);
    dp2(1);

    for(int i = 1; i <= n; i ++ )
    {
        fh[i][0][0][0] = INF;
        fh[i][0][1][0] = f[fa[i][0]][0] - f[i][1];
        fh[i][0][0][1] = f[fa[i][0]][1] - min(f[i][0], f[i][1]);
        fh[i][0][1][1] = f[fa[i][0]][1] - min(f[i][0], f[i][1]);
    }

    for(int j = 1; j <= 18; j ++ )
        for(int i = 1; i <= n; i ++ )
        {
            int tmp = fa[i][j - 1];
            fa[i][j] = fa[tmp][j - 1];
            for(int k = 0; k < 2; k ++ )
                for(int u = 0; u < 2; u ++ )
                {
                    fh[i][j][k][u] = INF;
                    for(int v = 0; v < 2; v ++ )
                        fh[i][j][k][u] = min(fh[i][j][k][u], fh[i][j - 1][k][v] + fh[tmp][j - 1][v][u]);
                }
        }

    while(m -- )
    {
        int x = read(), a = read(), y = read(), b = read();
        if(!a && !b && mp.count({x, y}))
        {
            puts("-1");
            continue;
        }
        printf("%lld\n", solve(x, a, y, b));
    }

    return 0;
}
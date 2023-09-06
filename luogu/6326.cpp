#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 1e6 + 10, NN = 1010, M = 4010, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
struct item
{
    // w is cost, V is value
    int w, v;
}p[N];
int w[N], cost[N], have[N];
int f[NN][M];
int ans;
int siz[N], maxsiz[N], rt;
bitset<N> vis;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1, maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        calc_siz(v, u, sz);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt])
    {
        rt = u;
    }
}

int dfn[N], out[N], anti[N], tim;

inline void dfs_dfn(int u, int fa)
{
    dfn[u] = ++ tim;
    anti[tim] = u;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        dfs_dfn(v, u);
    }
    out[u] = tim;
}

inline void dfz(int u)
{
    vis[u] = true;
    tim = 0;
    dfs_dfn(u, 0);
    for(int i = tim; i; i -- )
    {
        int cnt = 0, s = have[anti[i]] - 1;
        for(int j = 1; j <= s; j <<= 1)
        {
            p[++ cnt] = {j * cost[anti[i]], j * w[anti[i]]};
            s -= j;
        }
        if(s) p[++ cnt] = {s * cost[anti[i]], s * w[anti[i]]};

        for(int j = m; j >= cost[anti[i]]; j -- ) f[i][j] = f[i + 1][j - cost[anti[i]]] + w[anti[i]];
        for(int k = 1; k <= cnt; k ++ )
            for(int j = m; j >= p[k].w; j -- )
                f[i][j] = max(f[i][j], f[i][j - p[k].w] + p[k].v);
        for(int j = 0; j <= m; j ++ ) f[i][j] = max(f[i][j], f[out[anti[i]] + 1][j]);       
    }

    ans = max(ans, f[1][m]);
    for(int i = 0; i <= tim; i ++ )
        for(int j = 0; j <= m; j ++ )
            f[i][j] = 0;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;
        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(v, u, siz[u]);
        calc_siz(rt, rt, siz[v]);
        dfz(rt);
    }
}

inline void init()
{
    memset(h, -1, sizeof h);
    vis.reset();
    idx = ans = 0;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read(), m = read();

        init();

        for(int i = 1; i <= n; i ++ ) w[i] = read();
        for(int i = 1; i <= n; i ++ ) cost[i] = read();
        for(int i = 1; i <= n; i ++ ) have[i] = read();

        for(int i = 1; i < n; i ++ )
        {
            int a = read(), b = read();
            add(a, b), add(b, a);
        }

        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(1, 1, n);
        calc_siz(rt, rt, n);
        dfz(rt);

        cout << ans << endl;
    } 

    return 0;
}

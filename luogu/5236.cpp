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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int hs[N];
int n, m, q;

inline void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int ext;
int b[N], sum[N];
namespace tj
{
    int dfn[N], low[N], tim;
    int stk[N], tt;
    int fa[N];

    inline void solve(int u, int v, int w)
    {
        ++ ext;
        int pre = w, i = v;
        while(i != fa[u])
        {
            sum[i] = pre;
            pre += b[i];
            i = fa[i];
        }
        sum[ext] = sum[u];
        sum[u] = 0;
        i = v;
        while(i != fa[u])
        {
            int pw = min(sum[i], sum[ext] - sum[i]);
            add(hs, ext, i, pw);
            add(hs, i, ext, pw);
            i = fa[i];
        }
    }

    void tarjan(int u, int f)
    {
        dfn[u] = low[u] = ++ tim;
        stk[++ tt] = u;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            if(!dfn[v])
            {
                fa[v] = u, b[v] = w[i];
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
            }
            else low[u] = min(low[u], dfn[v]);

            if(low[v] <= dfn[u]) continue;
            add(hs, v, u, w[i]), add(hs, u, v, w[i]);
        }

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(fa[v] == u || dfn[v] <= dfn[u]) continue;
            solve(u, v, w[i]);
        }
    }
}

int fa[N >> 3][20], dep[N], dist[N];
void dfs(int u, int f)
{
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dist[v] = dist[u] + w[i];
        dfs(v, u);
    }
}

void init()
{
    for(int i = 1; i < 20; i ++ )
        for(int j = 1; j <= ext; j ++ )
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
}

inline int jump(int u, int f)
{
    for(int i = 19; i >= 0; i -- )  
        if(dep[fa[u][i]] > dep[f])
            u = fa[u][i];
    return u;
}

inline int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; i -- )
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];

    if(x == y) return x;

    for(int i = 19; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read(), q = read();
    ext = n;
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(h, a, b, c), add(h, b, a, c);
    }

    tj::tarjan(1, 0);
    dfs(1, 1);
    init();

    while(q -- )
    {
        int u = read(), v = read();
        int p = lca(u, v);
        if(p <= n) printf("%d\n", dist[u] + dist[v] - (dist[p] << 1));
        else
        {
            int A = jump(u, p), B = jump(v, p);
            int ans = dist[u] + dist[v] - dist[A] - dist[B];
            if(sum[A] < sum[B]) swap(A, B);
            ans += min(sum[A] - sum[B], sum[p] - sum[A] + sum[B]);
            printf("%d\n", ans);
        }
    }

    return 0;
}
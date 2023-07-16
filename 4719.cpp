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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
int val[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct matrix
{
    int a[2][2];
    matrix()
    {
        memset(a, 0, sizeof a);
    }

    inline int* operator [] (int x) 
    {
        return a[x];
    }

    matrix operator * (const matrix& M)
    {
        matrix tmp;
        for(int k = 0; k < 2; k ++ )
            for(int i = 0; i < 2; i ++ )
                for(int j = 0; j < 2; j ++ )
                    tmp.a[i][j] = max(tmp.a[i][j], a[i][k] + M.a[k][j]);
        return tmp;
    }
}g[N];

int f[N][2], fa[N], siz[N], son[N], dep[N];
void dfs1(int u, int fat)
{
    fa[u] = fat, dep[u] = dep[fat] + 1;
    siz[u] = 1;
    f[u][1] = val[u];
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fat) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(maxsiz < siz[v])
        {
            maxsiz = siz[v];
            son[u] = v;
        }
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int top[N], End[N], dfn[N], anti[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
    End[t] = tim;
    g[u][1][1] = -INF;
    g[u][1][0] = val[u];
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        g[u][1][0] += f[v][0];
        g[u][0][0] += max(f[v][0], f[v][1]);
    }
    g[u][0][1] = g[u][0][0];
}

struct seg
{
    int l, r;
    matrix a;
}t[N << 2];
int n, m;

inline void pushup(int p)
{
    t[p].a = t[p << 1].a * t[p << 1 | 1].a;
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].a = g[anti[l]];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change(int p, int pos)
{
    if(t[p].l == t[p].r)
    {
        t[p].a = g[anti[pos]];
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos);
    else change(p << 1 | 1, pos);
    pushup(p);
}

inline matrix query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].a;
    int mid = t[p].l + t[p].r >> 1;
    if(r <= mid) return query(p << 1, l, r);
    if(l > mid) return query(p << 1 | 1, l, r);
    return query(p << 1, l, r) * query(p << 1 | 1, l, r);
}

inline void update(int x, int v)
{
    g[x][1][0] += v - val[x];
    val[x] = v;
    while(x)
    {
        auto lst = query(1, dfn[top[x]], End[top[x]]);
        change(1, dfn[x]);
        auto now = query(1, dfn[top[x]], End[top[x]]);
        x = fa[top[x]];
        g[x][0][0] += max(now[0][0], now[1][0]) - max(lst[0][0], lst[1][0]);
        g[x][0][1] = g[x][0][0];
        g[x][1][0] += now[0][0] - lst[0][0];
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) val[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);

    while(m -- )
    {
        int x = read(), y = read();
        update(x, y);
        auto ans = query(1, dfn[1], End[top[1]]);
        printf("%d\n", max(ans[0][0], ans[1][0]));
    }

    return 0;
}

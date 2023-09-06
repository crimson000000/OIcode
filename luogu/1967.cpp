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

const int N = 1e6 + 10;
int p[N];
int h[N], e[N], ne[N], w[N], idx;
struct edge
{
    int u, v, w;
    bool operator < (const edge& a) const
    {
        return w > a.w;
    }
}ed[N];
int n, m, k;

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline void kruskal()
{
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].u, b = ed[i].v, c = ed[i].w;
        if(find(a) == find(b)) continue;
        p[find(a)] = find(b);
        add(a, b, c), add(b, a, c);
    }
}

int fa[N], v[N], dep[N], son[N], siz[N];
bitset<N> vis;
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        v[j] = w[i];
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsiz)
        {
            maxsiz = siz[j];
            son[u] = j;
        }
    }
}

int dfn[N], top[N], anti[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

struct segment
{
    int l, r;
    int minn;
}t[N << 2];

inline void pushup(int p)
{
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].minn = v[anti[l]];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].minn;
    int res = 0x3f3f3f3f;
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) res = min(res, query(p << 1, l, r));
    if(r > mid) res = min(res, query(p << 1 | 1, l, r));
    return res;
}

inline int qchain(int x, int y)
{
    int res = 0x3f3f3f3f;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = min(res, query(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    res = min(res, query(1, dfn[y] + 1, dfn[x]));
    return res;
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
        int u = read(), v = read(), w = read();
        ed[i] = {u, v, w};
    }

    for(int i = 1; i <= n; i ++ ) p[i] = i;

    sort(ed + 1, ed + m + 1);

    kruskal();

    k = read();
    
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            dfs1(i, i);
            dfs2(i, i);
            v[i] = 0x3f3f3f3f;
        }
    
    build(1, 1, n);
    
    while(k -- )
    {
        int x = read(), y = read();
        if(find(x) != find(y)) 
        {
            puts("-1");
            continue;
        }
        printf("%d\n", qchain(x, y));
    }

    return 0;
}
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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int n, m, cc;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize) 
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

int top[N], dfn[N], anti[N], tim;
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

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) return y;
    return x;
}

struct segmenttree
{
    struct segment
    {
        int l, r;
        int cnt, cov;
        int lc, rc;
    }t[N << 2];

    inline void pushup(segment &root, segment le, segment re)
    {
        root.lc = le.lc, root.rc = re.rc;
        if(le.rc == re.lc) root.cnt = le.cnt + re.cnt - 1;
        else root.cnt = le.cnt + re.cnt;
    }

    inline void pushup(int p)
    {
        pushup(t[p], t[p << 1], t[p << 1 | 1]);
    }

    inline void pushdown(int p)
    {
        if(t[p].cov)
        {
            t[p << 1].cov = t[p].cov;
            t[p << 1 | 1].cov = t[p].cov;
            t[p << 1].cnt = t[p << 1 | 1].cnt = 1;
            t[p << 1].lc = t[p << 1].rc = t[p << 1 | 1].lc = t[p << 1 | 1].rc = t[p].cov;
            t[p].cov = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r)
        {
            t[p].lc = t[p].rc = ++ cc;
            t[p].cnt = 1;
            t[p].cov = 0;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    void cover(int p, int l, int r, int c)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].lc = t[p].rc = c;
            t[p].cnt = 1;
            t[p].cov = c;
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) cover(p << 1, l, r, c);
        if(r > mid) cover(p << 1 | 1, l, r, c);
        pushup(p);
    }

    segment query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p];
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(r <= mid) return query(p << 1, l, r);
        if(l > mid) return query(p << 1 | 1, l, r);
        segment le = query(p << 1, l, r), re = query(p << 1 | 1, l, r);
        segment res;
        pushup(res, le, re);
        return res;
    }

    int query(int p, int pos)
    {
        if(t[p].l == t[p].r) return t[p].lc;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) return query(p << 1, pos);
        else return query(p << 1 | 1, pos);
    }
}t;

void cchain(int x, int y, int c)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        t.cover(1, dfn[top[x]], dfn[x], c);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.cover(1, dfn[y], dfn[x], c);
}

int qchain(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += t.query(1, dfn[top[x]], dfn[x]).cnt;
        if(t.query(1, dfn[top[x]]) == t.query(1, dfn[fa[top[x]]])) res --;
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    res += t.query(1, dfn[y], dfn[x]).cnt;
    return res;
}

void init()
{
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(t.t, 0, sizeof t.t);
    memset(fa, 0, sizeof fa);
    memset(top, 0, sizeof top);
    memset(siz, 0, sizeof siz);
    memset(dfn, 0, sizeof dfn);
    memset(anti, 0, sizeof anti);
    memset(son, 0, sizeof son);
    memset(dep, 0, sizeof dep);
    idx = cc = tim = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        init();
        n = read(), m = read();
        for(int i = 1; i < n; i ++ )
        {
            int a = read(), b = read();
            add(a, b), add(b, a);
        }

        dfs1(1, 1);
        dfs2(1, 1);
        t.build(1, 1, n);

        while(m -- )
        {
            int op = read(), a = read(), b = read();
            if(op == 1)
            {
                cchain(a, b, ++ cc);
            }
            else
            {
                printf("%d\n", dep[a] + dep[b] - 2 * dep[lca(a, b)] + 1 - qchain(a, b));
            }
        }
    }
    
    return 0;
}

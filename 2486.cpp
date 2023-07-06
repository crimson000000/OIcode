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
int col[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N];
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

struct segmenttree
{
    struct segment
    {
        int l, r;
        int lc, rc;
        int cnt, cov;
    }t[N << 2];

    inline void pushup(segment& root, segment le, segment re)
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
            t[p << 1].cnt = 1;
            t[p << 1 | 1].cnt = 1;
            t[p << 1].lc = t[p << 1].rc = t[p << 1 | 1].lc = t[p << 1 | 1].rc = t[p].cov;
            t[p].cov = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) 
        {
            t[p].cnt = 1;
            t[p].cov = 0;
            t[p].lc = t[p].rc = col[anti[l]];
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    void cover(int p, int l, int r, int color)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].cnt = 1;
            t[p].cov = t[p].lc = t[p].rc = color;
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) cover(p << 1, l, r, color);
        if(r > mid) cover(p << 1 | 1, l, r, color);
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) col[i] = read();

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
        char op[2];
        scanf("%s", op);
        if(op[0] == 'C')
        {
            int a = read(), b = read(), c = read();
            cchain(a, b, c);
        }
        else
        {
            int a = read(), b = read();
            printf("%d\n", qchain(a, b));
        }
    }
    
    return 0;
}

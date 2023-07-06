#define LOCAL
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

int h[N], e[N], ne[N], idx;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], son[N], siz[N];
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
        int cnt;
        int cov;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
    }
    
    inline void pushdown(int p)
    {
        if(t[p].cov == -1)
        {
            t[p << 1].cov = t[p << 1 | 1].cov = -1;
            t[p << 1].cnt = t[p << 1 | 1].cnt = 0;
            t[p].cov = 0;
        }
        if(t[p].cov == 1)
        {
            t[p << 1].cov = 1;
            t[p << 1 | 1].cov = 1;
            t[p << 1].cnt = t[p << 1].r - t[p << 1].l + 1;
            t[p << 1 | 1].cnt = t[p << 1 | 1].r - t[p << 1 | 1].l + 1;
            t[p].cov = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void cover(int p, int l, int r, bool one)
    {
        if(l > r) swap(l, r);
        if(t[p].l >= l && t[p].r <= r)
        {
            if(one)
            {
                t[p].cov = 1;
                t[p].cnt = t[p].r - t[p].l + 1;
            }
            else
            {
                t[p].cov = -1;
                t[p].cnt = 0;
            }
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) cover(p << 1, l, r, one);
        if(r > mid) cover(p << 1 | 1, l, r, one);
        pushup(p);
    }

    int query(int p, int l, int r, bool one)
    {
        if(l > r) swap(l, r);
        if(t[p].l >= l && t[p].r <= r)
        {
            if(one) return t[p].cnt;
            else return t[p].r - t[p].l + 1 - t[p].cnt;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        int cnt = 0;
        if(l <= mid) cnt += query(p << 1, l, r, one);
        if(r > mid) cnt += query(p << 1 | 1, l, r, one);
        return cnt;
    }
}t;

int qchain(int x, int y, bool one)
{
    int res = 0;
    
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += t.query(1, dfn[top[x]], dfn[x], one);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    
    res += t.query(1, dfn[x], dfn[y], one);
    return res;
}

void cchain(int x, int y, bool one)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        t.cover(1, dfn[top[x]], dfn[x], one);
        x = fa[top[x]];
    }
 
    if(dep[x] > dep[y]) swap(x, y);
    t.cover(1, dfn[x], dfn[y], one);
}

int qson(int x, bool one)
{
    return t.query(1, dfn[x], dfn[x] + siz[x] - 1, one);
}

void cson(int x, bool one)
{
    t.cover(1, dfn[x], dfn[x] + siz[x] - 1, one);
}

int install(int x)
{
    int res = qchain(0, x, 0);
    cchain(0, x, 1);
    return res;
}

int uninstall(int x)
{
    int res = qson(x, 1);
    cson(x, 0);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i < n; i ++ )
    {
        int f;
        scanf("%d", &f);
        add(f, i);
        add(i, f);
    }

    dfs1(0, 0);
    dfs2(0, 0);
    t.build(1, 1, n);

    scanf("%d", &m);
    while(m -- )
    {
        char op[20];
        int x;
        scanf("%s%d", op, &x);
        if(op[0] == 'i')
        {
            cout << install(x) << endl;
        }
        else
        {
            cout << uninstall(x) << endl;
        }
    }

    return 0;
}
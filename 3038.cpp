#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 1e5 + 10, M = 2e5 + 10;
int h[N], e[M], ne[M], idx;
int fa[N], siz[N], top[N], son[N], dep[N], a[N];
int dfn[N], w[N], tim;
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        a[j] = w[i];
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    w[tim] = u;
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
    int val, add;
}t[N * 4];

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].val = a[w[l]];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid); 
    build(p << 1 | 1, mid + 1, r);    
}

inline void pushup(int p)
{
    t[p].val = t[p << 1].val + t[p << 1 | 1].val;
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        int a = t[p].add;
        t[p << 1].val += (t[p << 1].r - t[p << 1].l + 1) * a;
        t[p << 1 | 1].val += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * a;
        t[p << 1].add += a;
        t[p << 1 | 1].add += a;
        t[p].add = 0;
    }
}

void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].val += (t[p].r - t[p].l + 1) * val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
        return t[p].val;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum += query(p << 1, l, r);
    if(r > mid) sum += query(p << 1 | 1, l, r);
    return sum;
}

void mchain(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change(1, dfn[top[x]], dfn[x], 1);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    change(1, dfn[x], dfn[y], 1);
    change(1, dfn[x], dfn[x], -1);
}

int qchain(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += query(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res += query(1, dfn[x], dfn[y]);
    res -= query(1, dfn[x], dfn[x]);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    n = read(), m = read();

    memset(h, -1, sizeof h);

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b, 0), add(b, a, 0);
    }

    dfs1(1, 1);
    
    dfs2(1, 1);
    build(1, 1, n);

    while(m -- )
    {
        char op[2];
        scanf("%s", op);
        int x = read(), y = read();
        if(op[0] == 'P')
        {
            mchain(x, y);
        }
        else
        {
            cout << qchain(x, y) << endl;
        }
    }
   
    return 0;
}

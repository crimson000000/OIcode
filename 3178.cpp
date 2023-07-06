#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
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

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
int v[N];
int n, m;

void add(int a, int b)
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

int dfn[N], w[N], top[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    w[tim] = v[u];
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
    int sum, add;
}t[N * 4];

void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

void pushdown(int p)
{
    if(t[p].add)
    {
        int a = t[p].add;
        t[p << 1].add += a;
        t[p << 1 | 1].add += a;
        t[p << 1].sum += a * (t[p << 1].r - t[p << 1].l + 1);
        t[p << 1 | 1].sum += a * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1);
        t[p].add = 0;
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].sum = w[l];
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change1(int p, int x, int val)
{
    if(t[p].l == t[p].r) 
    {
        t[p].sum += val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(x <= mid) change1(p << 1, x, val);
    else change1(p << 1 | 1, x, val);
    pushup(p);
}

void change2(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].sum += (t[p].r - t[p].l + 1) * val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change2(p << 1, l, r, val);
    if(r > mid) change2(p << 1 | 1, l, r, val);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum += query(p << 1, l, r);
    if(r > mid) sum += query(p << 1 | 1, l, r);
    return sum;
}

void mpoint(int x, int a)
{
    change1(1, dfn[x], a);
}

void change(int x, int y, int a)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change2(1, dfn[top[x]], dfn[x], a);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    change2(1, dfn[x], dfn[y], a);
}

void mson(int x, int a)
{
    change2(1, dfn[x], dfn[x] + siz[x] - 1, a);
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
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) v[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    while(m -- )
    {
        int op, x, a;
        op = read();
        x = read();
        if(op == 1)
        {
            a = read();
            mpoint(x, a);
        }
        else if(op == 2)
        {
            a = read();
            mson(x, a);
        }
        else
        {
            cout << qchain(1, x) << endl;
        }
    }

    return 0;
}

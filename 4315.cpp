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

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], w[M], idx, to[M], fr[M];
int n;

void add(int a, int b, int c)
{
    e[idx] = b, to[idx] = b, fr[idx] = a, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N], v[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        v[j] = w[i];
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
    anti[tim] = v[u];
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
    int val;
    int add, cov;
}t[N * 4];

void pushup(int p)
{
    t[p].val = max(t[p << 1].val, t[p << 1 | 1].val);
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].cov = -1;
    if(l == r)
    {
        t[p].val = anti[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void pushdown(int p)
{
    if(t[p].cov != -1)
    {
        t[p << 1].val = t[p].cov;
        t[p << 1 | 1].val = t[p].cov;
        t[p << 1].cov = t[p].cov;
        t[p << 1 | 1].cov = t[p].cov;
        t[p << 1].add = 0;
        t[p << 1 | 1].add = 0;
        t[p].cov = -1;
    }
    if(t[p].add)
    {
        t[p << 1].val += t[p].add;
        t[p << 1 | 1].val += t[p].add;
        t[p << 1].add += t[p].add;
        t[p << 1 | 1].add += t[p].add;
        t[p].add = 0;
    }
}

void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].val += val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

void cover(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].cov = val;
        t[p].add = 0;
        t[p].val = val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cover(p << 1, l, r, val);
    if(r > mid) cover(p << 1 | 1, l, r, val);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].val;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum = max(sum, query(p << 1, l, r));
    if(r > mid) sum = max(sum, query(p << 1 | 1, l, r));
    return sum;
}

void coverchain(int x, int y, int val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        cover(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    cover(1, dfn[x] + 1, dfn[y], val);
}

void achain(int x, int y, int val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    change(1, dfn[x] + 1, dfn[y], val);
}

int qchain(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, query(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res = max(res, query(1, dfn[x] + 1, dfn[y]));
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    memset(h, -1, sizeof h);
   
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    char op[10];
    int a, b, k, val;
    while(scanf("%s", op), op[0] != 'S')
    {
        if(op[0] == 'M')
        {
            a = read(), b = read();
            cout << qchain(a, b) << endl;
        }
        else if(op[0] == 'C' && op[1] == 'h')
        {
            k = read(), val = read();
            k = 2 * (k - 1);
            int a = to[k], b = fr[k];
            if(dep[a] > dep[b]) swap(a, b);
            coverchain(a, b, val);
        }
        else if(op[0] == 'C')
        {
            a = read(), b = read(), val = read();
            coverchain(a, b, val);
        }
        else
        {
            a = read(), b = read(), val = read();
            achain(a, b, val);
        }
    }
    
    return 0;
}

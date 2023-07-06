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

const int N = 1e5 + 10, M = N * 2;
int h[N], e[M], ne[M], idx;
int v[N];
int n, m, r, mod;

void add(int a, int b)
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
            son[u] = j;
            maxsize = siz[j];
        }
    }
}

int top[N], dfn[N], tim, w[N];
void dfs2(int u, int t)
{
    dfn[u] = ++ tim;
    top[u] = t;
    w[tim] = v[u] % mod;
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

inline void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].sum = w[l] % mod;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void pushdown(int p)
{
    if(t[p].add)
    {
        int a = t[p].add;
        t[p << 1].add = (t[p << 1].add + a) % mod;
        t[p << 1 | 1].add = (t[p << 1 | 1].add + a) % mod;
        t[p << 1].sum = (t[p << 1].sum + (ll)(t[p << 1].r - t[p << 1].l + 1) * a) % mod;
        t[p << 1 | 1].sum = (t[p << 1 | 1].sum + (ll)(t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * a) % mod;
        t[p].add = 0;
    }
}

void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add = (val + t[p].add) % mod;
        t[p].sum = (t[p].sum + (ll)val * (t[p].r - t[p].l + 1)) % mod;
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
    {
        return t[p].sum;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum = (sum + query(p << 1, l, r)) % mod;
    if(r > mid) sum = (sum + query(p << 1 | 1, l, r)) % mod;
    return sum;
}

void cson(int x, int z)
{
    change(1, dfn[x], dfn[x] + siz[x] - 1, z);
}

inline int qson(int x)
{
    return query(1, dfn[x], dfn[x] + siz[x] - 1);
}

void mchain(int x, int y, int val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        change(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    change(1, dfn[x], dfn[y], val);
}

int qchain(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        res = (res + query(1, dfn[top[x]], dfn[x])) % mod;
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res = (res + query(1, dfn[x], dfn[y])) % mod;
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    n = read(), m = read(), r = read(), mod = read();
    memset(h, -1, sizeof h);

    for(int i = 1; i <= n; i ++ ) v[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    
    dfs1(1, r);
    dfs2(r, r);
    build(1, 1, n);
    
    while(m -- )
    {
        int op, x, y, z;
        op = read();
        if(op == 1)
        {
            x = read(), y = read(), z = read();
            mchain(x, y, z);
        }
        else if(op == 2)
        {
            x = read(), y = read();
            cout << qchain(x, y) % mod << endl;
        }
        else if(op == 3)
        {
            x = read(), z = read();
            cson(x, z);
        }
        else
        {
            x = read();
            cout << qson(x) % mod << endl;
        }
    }

    return 0;
}
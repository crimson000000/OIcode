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
int h[N], e[M], ne[M], idx;
int v[N], fa[N], dep[N], son[N], siz[N];
int n, q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
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
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

int top[N], dfn[N], w[N], tim;
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
    int sum, dat;
}t[N * 4];

void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].dat = max(t[p << 1].dat, t[p << 1 | 1].dat);
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].sum = t[p].dat = w[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int x, int val)
{
    if(t[p].l == t[p].r)
    {
        t[p].sum = val;
        t[p].dat = val;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(x <= mid) change(p << 1, x, val);
    else change(p << 1 | 1, x, val);
    pushup(p);
}

int querysum(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].sum;
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum += querysum(p << 1, l, r);
    if(r > mid) sum += querysum(p << 1 | 1, l, r);
    return sum;
}

int querymax(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].dat;
    int mid = t[p].l + t[p].r >> 1;
    int res = -0x3f3f3f3f;
    if(l <= mid) res = max(res, querymax(p << 1, l, r));
    if(r > mid) res = max(res, querymax(p << 1 | 1, l, r));
    return res;
}

void mpoint(int x, int t)
{
    change(1, dfn[x], t);
}

int qmax(int x, int y)
{
    int res = -0x3f3f3f3f;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, querymax(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res = max(res, querymax(1, dfn[x], dfn[y]));
    return res;
}

int qsum(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += querysum(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res += querysum(1, dfn[x], dfn[y]);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    for(int i = 1; i <= n; i ++ ) v[i] = read();
    dfs1(1, 1);
    
    dfs2(1, 1);
    build(1, 1, n);

    q = read();
    while(q -- )
    {
        char op[10];
        scanf("%s", op);
        int u = read(), v = read();
        if(op[0] == 'C')
        {
            mpoint(u, v);
        }  
        else if(op[1] == 'M')
        {
            cout << qmax(u, v) << endl;
        } 
        else
        {
            cout << qsum(u, v) << endl;
        }
    }
   
    return 0;
}

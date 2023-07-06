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
int h[N], e[M], ne[M], w[M], idx;
int v[N], fa[N], siz[N], son[N], dep[N];
int n;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int father)
{
    fa[u] = father, siz[u] = 1;
    dep[u] = dep[father] + 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;

        dfs1(j, u);
        v[j] = w[i];
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            son[u] = j;
            maxsize = siz[j];
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

struct segment
{
    int l, r;
    int dat;
    bool cov;
}t[N * 4];

void pushup(int p)
{
    t[p].dat = max(t[p << 1].dat, t[p << 1 | 1].dat);
}

void pushdown(int p)
{
    if(t[p].cov)
    {
        t[p << 1].dat = t[p].dat;
        t[p << 1 | 1].dat = t[p].dat;
        t[p].cov = false;
        t[p << 1].cov = true;
        t[p << 1 | 1].cov = true; 
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) 
    {
        t[p].dat = w[anti[l]];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void cover(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].dat = val;
        t[p].cov = true;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cover(p << 1, l, r, val);
    if(r > mid) cover(p << 1 | 1, l, r, val);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        return t[p].dat;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int res = -1;
    if(l <= mid) res = max(res, query(p << 1, l, r));
    if(r > mid) res = max(res, query(p << 1 | 1, l, r));
    return res;
}

void mchain(int x, int y, int val)
{
    while(dep[top[x]] != dep[top[y]])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        cover(1, dfn[top[x]], dfn[top[y]], val);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    cover(1, dfn[x], dfn[y], val);
}

int qchain(int x, int y)
{
    int res = 0;
    while(dep[top[x]] != dep[top[y]])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, query(1, dfn[top[x]], dfn[top[y]]));
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    res = max(res, query(1, dfn[x], dfn[y]));
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

    char op[20];
    scanf("%s", op);
    while(op[0] != 'D')
    {
        int a = read(), b = read();
        if(op[0] == 'Q')
        {
            if(a == b) cout << 0 << endl;
            else cout << qchain(a, b) << endl;
        }
        else
        {
            
        }
    }
    
    return 0;
}

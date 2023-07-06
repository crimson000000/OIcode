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
int h[N], e[N], ne[N], idx;
int v[N], color[N];
int n, m, q, c;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], siz[N], son[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsiz)
        {
            son[u] = j;
            maxsiz = siz[j];
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

struct node
{
    int l, r;
    double si, si2;
    double add;
}t[N * 60];
int cnt, root[N];

inline void pushup(int p)
{
    t[p].si = t[t[p].l].si + t[t[p].r].si;
    t[p].si2 = t[t[p].l].si2 + t[t[p].r].si2;
}

inline void tag(int &p, int l, int r, double val)
{
    if(!p) p = ++ cnt;
    t[p].add += val;
    t[p].si2 += 2 * val * t[p].si + val * val * (r - l + 1);
    t[p].si += val * (r - l + 1);
}

inline void pushdown(int p, int l, int r)
{
    if(t[p].add)
    {
        int mid = l + r >> 1;
        tag(t[p].l, l, mid, t[p].add);
        tag(t[p].r, mid + 1, r, t[p].add);
        t[p].add = 0;
    }
}

inline void change(int &p, int l, int r, int L, int R, double val)
{
    if(!p) p = ++ cnt;
    if(l >= L && r <= R)
    {
        tag(p, l, r, val);
        return;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1;
    if(L <= mid) change(t[p].l, l, mid, L, R, val);
    if(R > mid) change(t[p].r, mid + 1, r, L, R, val);
    pushup(p);
}

inline void cchain(int x, int y, int co, double val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change(root[co], 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    change(root[co], 1, n, dfn[y], dfn[x], val);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read(), q = read(), c = read();

    for(int i = 1; i <= n; i ++ ) color[i] = read();

    for(int i = 2; i <= n; i ++ )
    {
        int x = read();
        add(i, x), add(x, i);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ ) cchain(1, i, color[i], 1);

    for(int i = 1; i <= m; i ++ ) v[i] = read();

    while(q -- )
    {
        int op = read(), x = read();
        if(op == 1)
        {
            int y = read();
            cchain(1, x, color[x], -1);
            cchain(1, x, y, 1);
            color[x] = y;
        }
        else
        {
            double si2 = t[root[x]].si2, si = t[root[x]].si;
            printf("%lf\n", (double)((double)v[x] * v[x] * si2 - 2 * (double)c * v[x] * si) / n + (double)c * c);
        }
    }

    return 0;
}
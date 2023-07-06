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
int w[N];
int d[N];
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct node
{
    int l, r;
    int val;
}t[N * 20];
int cnt;
int root[N];

void insert(int &p, int l, int r, int pos, int val)
{
    if(!p) p = ++ cnt;
    if(l == r) 
    {
        t[p].val += val;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, l, mid, pos, val);
    else insert(t[p].r, mid + 1, r, pos, val);
}

int query(int p, int l, int r, int pos)
{
    if(!p) return 0;
    if(l == r) return t[p].val;
    int mid = l + r >> 1;
    if(pos <= mid) return query(t[p].l, l, mid, pos);
    else return query(t[p].r, mid + 1, r, pos);
}

int merge(int a, int b, int l = 1, int r = (n << 1))
{
    if(!a || !b) return a + b;
    if(l == r) 
    {
        t[a].val += t[b].val;
        return a;
    } 
    int mid = l + r >> 1;
    t[a].l = merge(t[a].l, t[b].l, l, mid);
    t[a].r = merge(t[a].r, t[b].r, mid + 1, r);
    return a;
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
        if(maxsiz < siz[j])
        {
            son[u] = j;
            maxsiz = siz[j];
        }
    }
}

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
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
    if(dep[x] < dep[y]) return x;
    return y;
}

int ans[N];
void dfs(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u]) continue;
        dfs(v);
        root[u] = merge(root[u], root[v]);
    }
    if(w[u] && n + dep[u] + w[u] <= (n << 1))
        ans[u] += query(root[u], 1, n << 1, n + dep[u] + w[u]);
    ans[u] += query(root[u], 1, n << 1, n + dep[u] - w[u]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ ) w[i] = read();

    while(m -- )
    {
        int x = read(), y = read();
        int anc = lca(x, y);
        insert(root[x], 1, n << 1, n + dep[x], 1);
        insert(root[y], 1, n << 1, n + 2 * dep[anc] - dep[x], 1);
        insert(root[anc], 1, n << 1, n + dep[x], -1);
        insert(root[fa[anc]], 1, n << 1, n + 2 * dep[anc] - dep[x], -1);
    }

    dfs(1);

    for(int i = 1; i <= n; i ++ ) printf("%d ", ans[i]);

    return 0;
}
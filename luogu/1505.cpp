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

const int N = 4e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int v[N];
int n, m;

struct edge
{
    int a, b;
}edges[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], son[N], siz[N], dep[N];
void dfs1(int u, int father)
{
    fa[u] = father, dep[u] = dep[father] + 1;
    siz[u] = 1;
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
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

int dfn[N], anti[N], top[N], tim;
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
    int maxn, minn, sum;
    bool swp;
}t[N * 4];

inline void pushup(int p)
{
    t[p].maxn = max(t[p << 1].maxn, t[p << 1 | 1].maxn);
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

inline void to_nega(int p)
{
    t[p].swp ^= 1;
    t[p].maxn *= -1;
    t[p].minn *= -1;
    t[p].sum *= -1;
    swap(t[p].maxn, t[p].minn);
}

inline void pushdown(int p)
{
    if(t[p].swp)
    {
        to_nega(p << 1);
        to_nega(p << 1 | 1);
        t[p].swp = false;
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].maxn = t[p].minn = t[p].sum = anti[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int pos, int x)
{
    if(t[p].l == t[p].r)
    {
        t[p].maxn = t[p].minn = t[p].sum = x;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos, x);
    else change(p << 1 | 1, pos, x);
    pushup(p);
}

void nega(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        to_nega(p);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) nega(p << 1, l, r);
    if(r > mid) nega(p << 1 | 1, l, r);
    pushup(p);
}

int query_sum(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
        return t[p].sum;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum += query_sum(p << 1, l, r);
    if(r > mid) sum += query_sum(p << 1 | 1, l, r);
    return sum;
}

int query_max(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
        return t[p].maxn;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int maxn = -INF;
    if(l <= mid) maxn = max(maxn, query_max(p << 1, l, r));
    if(r > mid) maxn = max(maxn, query_max(p << 1 | 1, l, r));
    return maxn;
}

int query_min(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
        return t[p].minn;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int minn = INF;
    if(l <= mid) minn = min(minn, query_min(p << 1, l, r));
    if(r > mid) minn = min(minn, query_min(p << 1 | 1, l, r));
    return minn;
}

void nega_chain(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        nega(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    if(x != y) nega(1, dfn[y] + 1, dfn[x]);
}

int qmax_chain(int x, int y)
{
    int maxn = -INF;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        maxn = max(maxn, query_max(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    if(x != y) maxn = max(maxn, query_max(1, dfn[y] + 1, dfn[x]));
    return maxn;
}

int qmin_chain(int x, int y)
{
    int minn = INF;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        minn = min(minn, query_min(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    if(x != y) minn = min(minn, query_min(1, dfn[y] + 1, dfn[x]));
    return minn;
}

int sum_chain(int x, int y)
{
    int sum = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        sum += query_sum(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    if(x != y) sum += query_sum(1, dfn[y] + 1, dfn[x]);
    return sum;
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
        int a = read() + 1, b = read() + 1, c = read();
        add(a, b, c), add(b, a, c);
        edges[i] = {a, b};
    }

    dfs1(1, 1);
    dfs2(1, 1);

    build(1, 1, n);

    m = read();

    while(m -- )
    {
        char op[5];
        scanf("%s", op);
        int x = read(), y = read();
        if(op[0] == 'C')
        {
            int t;
            int a = edges[x].a, b = edges[x].b;
            if(dep[a] > dep[b]) t = a;
            else t = b;
            change(1, dfn[t], y);
        }
        else if(op[0] == 'N')
        {
            nega_chain(x + 1, y + 1);
        }
        else if(op[1] == 'U')
        {
            cout << sum_chain(x + 1, y + 1) << endl;
        }
        else if(op[1] == 'A')
        {
            cout << qmax_chain(x + 1, y + 1) << endl;
        }
        else
        {
            cout << qmin_chain(x + 1, y + 1) << endl;
        }
    }

    return 0;
}

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
int n, m;

struct edge
{
    int a, b;
    bool del;
    int tim;
    int id;
    bool operator < (const edge& t) const
    {
        return tim < t.tim;
    }
}act[N];

map<PII, int> mp;
int ans[N], tt, idd;

int p[N];
inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void kruskal()
{
    for(int i = 1; i <= n; i ++ ) p[i] = i;
    for(int i = 1; i <= m; i ++ )
    {
        int a = act[i].a, b = act[i].b;
        if(act[i].del) continue;
        if(find(a) == find(b))
        {
            act[i].del = true;
            act[i].tim = 0x3f3f3f3f;
            continue;
        }
        p[find(a)] = find(b);
        add(a, b), add(b, a);
    }
}

struct node
{
    int l, r;
    int cnt, cov;
}t[N << 2];

inline void pushup(int p)
{
    t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
}

inline void cover(int p)
{
    t[p].cnt = 0;
    t[p].cov = 1;
}

inline void pushdown(int p)
{
    if(t[p].cov)
    {
        cover(p << 1);
        cover(p << 1 | 1);
        t[p].cov = 0;
    }
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].cov = 0;
    if(l == r)
    {
        t[p].cnt = 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void cover(int p, int l, int r)
{
    if(l > r) return;
    if(t[p].l >= l && t[p].r <= r)
    {
        cover(p);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cover(p << 1, l, r);
    if(r > mid) cover(p << 1 | 1, l, r);
    pushup(p);
}

inline int query(int p, int l, int r)
{
    if(l > r) return 0;
    if(t[p].l >= l && t[p].r <= r) return t[p].cnt;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int res = 0;
    if(l <= mid) res += query(p << 1, l, r);
    if(r > mid) res += query(p << 1 | 1, l, r);
    return res;
}

int fa[N], siz[N], son[N], dep[N];
void dfs1(int u, int f)
{
    fa[u] = f, siz[u] = 1;
    dep[u] = dep[f] + 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
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

void cchain(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        cover(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    cover(1, dfn[y] + 1, dfn[x]);
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
    if(dep[x] < dep[y]) swap(x, y);
    res += query(1, dfn[y] + 1, dfn[x]);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        act[i] = {a, b, false, 0, -1};
        mp[{a, b}] = i;
        mp[{b, a}] = i;
    }

    tt = m;

    while(1)
    {
        int op = read();
        if(op == -1) break;
        int x = read(), y = read();
        if(op == 1)
        {
            tt ++;
            idd ++;
            act[tt] = {x, y, false, tt, idd}; 
        }
        else
        {
            tt ++;
            int id = mp[{x, y}];
            act[id].del = true;
            act[id].tim = tt;
        }
    }

    kruskal();
    
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    sort(act + 1, act + tt + 1);
    reverse(act + 1, act + tt + 1);

    // for(int i = 1; i <= tt; i ++ ) 
    // {
    //     printf("%d %d %d %d\n", act[i].a, act[i].b, act[i].tim, act[i].id);
    // }

    for(int i = 1; i <= tt; i ++ )
    {
        if(act[i].tim == 0) break;
        if(act[i].id != -1)
        {
            ans[act[i].id] = qchain(act[i].a, act[i].b);
        }
        else
        {
            cchain(act[i].a, act[i].b);
        }
    }

    for(int i = 1; i <= idd; i ++ ) printf("%d\n", ans[i]);

    return 0;
}
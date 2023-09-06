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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 201314;
int h[N], e[N], ne[N], idx;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dep[N], fa[N], son[N], siz[N];
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, fa[u] = f;
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

struct segmenttree
{
    struct segment
    {
        int l, r;
        ll sum, add;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].sum = (t[p << 1].sum + t[p << 1 | 1].sum) % mod;
    }

    inline void pushdown(int p)
    {
        if(t[p].add)
        {
            t[p << 1].add = (t[p << 1].add + t[p].add) % mod;
            t[p << 1 | 1].add = (t[p << 1 | 1].add + t[p].add) % mod;
            t[p << 1].sum = (t[p << 1].sum + (t[p << 1].r - t[p << 1].l + 1) * t[p].add % mod) % mod;
            t[p << 1 | 1].sum = (t[p << 1 | 1].sum + (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].add % mod) % mod;
            t[p].add = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void change(int p, int l, int r, int val)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].add = (t[p].add + val) % mod;
            t[p].sum = ((ll)(t[p].r - t[p].l + 1) * val % mod + t[p].sum) % mod;
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
            return t[p].sum;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        int res = 0;
        if(l <= mid) res = (res + query(p << 1, l, r)) % mod;
        if(r > mid) res = (res + query(p << 1 | 1, l, r)) % mod;
        return res;
    }
}t;

void cchain(int x, int y, int val)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        t.change(1, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.change(1, dfn[y], dfn[x], val);
}

int qchain(int x, int y)
{
    int res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = (res + t.query(1, dfn[top[x]], dfn[x])) % mod;
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    res = (res + t.query(1, dfn[y], dfn[x])) % mod;
    return res;
}

struct query
{
    int op, pos, z;
    bool first;
    bool operator < (const query& Q) const
    {
        return pos < Q.pos;
    }
}q[N];
int tt, cur;
vector<int> Q[N];
int ans[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 2; i <= n; i ++ )
    {
        int x = read() + 1;
        add(i, x), add(x, i);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    t.build(1, 1, n);

    for(int i = 1; i <= m; i ++ )
    {
        int l = read() + 1, r = read() + 1, z = read() + 1;
        q[++ tt] = {i, l - 1, z, true};
        q[++ tt] = {i, r, z, false};
    }

    sort(q + 1, q + tt + 1);
    for(int i = 1; i <= tt; i ++ )
    {
        while(cur < q[i].pos) 
        {
            cur ++;
            cchain(1, cur, 1);
        }
        if(q[i].first) ans[q[i].op] = (ans[q[i].op] - qchain(1, q[i].z) + mod) % mod;
        else ans[q[i].op] = (ans[q[i].op] + qchain(1, q[i].z)) % mod;
    }

    for(int i = 1; i <= m; i ++ ) 
        printf("%d\n", ans[i]);
    
    return 0;
}
 
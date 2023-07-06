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

const int N = 1e6 + 10, mod = 998244353;
int h[N], e[N], ne[N], idx;
int n, m, k;

inline void add(int a, int b)
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

ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

struct segmenttree
{
    struct segment
    {
        int l, r;
        ll sum, s, cnt;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].sum = (t[p << 1].sum + t[p << 1 | 1].sum) % mod;
    }

    inline void pushdown(int p)
    {
        if(t[p].cnt > 0)
        {
            t[p << 1].sum = (t[p << 1].sum + t[p << 1].s * t[p].cnt) % mod;
            t[p << 1 | 1].sum = (t[p << 1 | 1].sum + t[p << 1 | 1].s * t[p].cnt) % mod;
            t[p << 1].cnt = (t[p << 1].cnt + t[p].cnt) % mod;
            t[p << 1 | 1].cnt = (t[p << 1 | 1].cnt + t[p].cnt) % mod;
            t[p].cnt = 0;
        }
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) 
        {
            t[p].s = (qmi(dep[anti[l]], k, mod) - qmi(dep[anti[l]] - 1, k, mod) + mod) % mod;
            t[p].sum = t[p].cnt = 0;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        t[p].s = (t[p << 1].s + t[p << 1 | 1].s) % mod;
    }

    void change(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].cnt ++;
            t[p].sum = (t[p].sum + t[p].s) % mod;
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) change(p << 1, l, r);
        if(r > mid) change(p << 1 | 1, l, r);
        pushup(p);
    }

    ll query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r)
            return t[p].sum;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        ll res = 0;
        if(l <= mid) res = (res + query(p << 1, l, r)) % mod;
        if(r > mid) res = (res + query(p << 1 | 1, l, r)) % mod;
        return res;
    }
}t;

void cchain(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        t.change(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    t.change(1, dfn[x], dfn[y]);
}

ll qchain(int x, int y)
{
    ll res = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res = (res + t.query(1, dfn[top[x]], dfn[x])) % mod;
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    res = (res + t.query(1, dfn[x], dfn[y])) % mod;
    return res;
}

struct query
{
    int op, p, z;
    bool operator < (const query& Q) const
    {
        return p < Q.p;
    }
}q[N];
int cur;
int ans[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), k = read();
    for(int i = 2; i <= n; i ++ )
    {
        int x = read();
        add(x, i), add(i, x);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    t.build(1, 1, n);
    
    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read();
        q[i] = {i, x, y};
    }

    sort(q + 1, q + 1 + m);
    for(int i = 1; i <= m; i ++ )
    {
        while(cur < q[i].p) 
        {
            cur ++;
            cchain(1, cur);
        }
        ans[q[i].op] = qchain(1, q[i].z);
    }

    for(int i = 1; i <= m; i ++ ) 
        printf("%d\n", ans[i]);

    return 0;
}

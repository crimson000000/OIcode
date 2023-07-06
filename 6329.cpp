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

const int N = 2e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int n, m;
ll lastans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace cao
{
    int fa[N], dep[N], siz[N], son[N];
    void dfs1(int u, int f)
    {
        fa[u] = f, dep[u] = dep[f] + 1;
        siz[u] = 1;
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

    int top[N];
    inline void dfs2(int u, int t)
    {
        top[u] = t;
        if(!son[u]) return;
        dfs2(son[u], t);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
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

    inline int dist(int x, int y)
    {
        return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
    }
}

int root[N][2];
namespace sgm
{
    struct node
    {
        int l, r;
        ll sum;
    }t[N * 20];
    int cnt;

    inline void pushup(int p)
    {
        t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
    }

    inline void insert(int &p, int l, int r, int pos, int val)
    {
        if(pos < l || pos > r) return;
        if(!p) p = ++ cnt;
        t[p].sum += val;
        if(l == r)
        {
            return;
        }
        int mid = l + r >> 1;
        if(pos <= mid) insert(t[p].l, l, mid, pos, val);
        else insert(t[p].r, mid + 1, r, pos, val);
    }

    inline ll query(int p, int l, int r, int L, int R)
    {
        if(L > R) return 0;
        if(R < l || r < L) return 0;
        if(!p) return 0;
        if(L <= l && r <= R) return t[p].sum;
        int mid = l + r >> 1;
        ll res = 0;
        if(L <= mid) res += query(t[p].l, l, mid, L, R);
        if(R > mid) res += query(t[p].r, mid + 1, r, L, R);
        return res;
    }
}

int maxsiz[N], siz[N], rt;
bitset<N> vis;
inline void calcsiz(int u, int fa, int sz)
{
    maxsiz[u] = 0;
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        calcsiz(v, u, sz);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt])
    {
        rt = u;
    }
}

inline void find_root(int u)
{
    rt = 0;
    maxsiz[rt] = INF;
    calcsiz(u, 0, siz[u]);
    calcsiz(rt, 0, siz[u]);
}

inline void dfs(int u, int fa, int dep, int op, int to)
{
    sgm::insert(root[to][op], 0, n, dep, w[u]);
    // printf("%d has given to %d by %d in %d\n", w[u], to, u, dep);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        dfs(v, u, dep + 1, op, to);
    }
}

int par[N];
void dfz(int u)
{
    vis[u] = true;
    dfs(u, 0, 0, 0, u);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;
        find_root(v);
        par[rt] = u;
        dfs(v, 0, 1, 1, rt);
        dfz(rt);
    }
}

inline ll query(int x, int k)
{
    ll res = 0;
    res += sgm::query(root[x][0], 0, n, 0, k);
    for(int i = x; par[i]; i = par[i])
    {
        int d = cao::dist(par[i], x);
        res += sgm::query(root[par[i]][0], 0, n, 0, k - d);
        res -= sgm::query(root[i][1], 0, n, 0, k - d);
    }
    return res;
}

inline void change(int x, ll to)
{
    ll delta = to - w[x];
    w[x] += delta;
    int y = x;
    sgm::insert(root[x][0], 0, n, 0, delta);
    for(int i = x; par[i]; i = par[i])
    {
        int d = cao::dist(par[i], x);
        sgm::insert(root[par[i]][0], 0, n, d, delta);
        sgm::insert(root[i][1], 0, n, d, delta);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();
    
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    cao::dfs1(1, 0);
    cerr << "i love SbF5" << endl;
    cao::dfs2(1, 1);

    

    rt = 0;
    maxsiz[rt] = INF;
    calcsiz(1, 1, n);
    calcsiz(rt, rt, n);
    dfz(rt);

    // for(int i = 1; i <= n; i ++ ) cout << par[i] << endl;
    
    // cout << sgm::query(root[1][0], 0, n, 0, 2) << endl;

    while(m -- )
    {
        ll op = read(), x = read() ^ lastans, y = read() ^ lastans;
        if(!op)
        {
            printf("%lld\n", lastans = query(x, y));
        }
        else
        {
            change(x, y);
        }
    }

    return 0;
}

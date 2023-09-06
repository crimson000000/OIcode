#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
int n, m, q;
int h[N], e[N], ne[N], idx;
int val[N];
int cnt;
int rt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

struct Ed
{
    int a, b, w;
}ed[N];

namespace Kru
{
    int fa[N];
    inline int find(int x)
    {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }

    inline void kruskal()
    {
        for(int i = 1; i <= 2 * n; i ++ ) fa[i] = i;
        for(int i = 1; i <= m; i ++ )
        {
            int a = ed[i].a, b = ed[i].b, w = ed[i].w;
            if(find(a) == find(b)) continue;
            cnt ++;
            rt = cnt;
            val[cnt] = w;
            add(find(a), cnt), add(cnt, find(a));
            add(find(b), cnt), add(cnt, find(b));
            fa[find(a)] = fa[find(b)] = find(cnt);
        }
    }
}

int fa[N], siz[N], dep[N], son[N];
inline void dfs1(int u, int f)
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

namespace ST
{
    int f[100010][20];
    inline void init()
    {
        for(int i = 1; i < n; i ++ ) f[i][0] = val[lca(i, i + 1)];
        for(int i = 1; i <= 18; i ++ )
            for(int j = 1; j + (1 << i) - 1 < n; j ++ )
                f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
    }

    inline int query(int l, int r)
    {
        int k = log2(r - l + 1);
        return max(f[l][k], f[r - (1 << k) + 1][k]);
    }
}

inline void init()
{
    for(int i = 1; i <= cnt; i ++ ) h[i] = -1, val[i] = 0;
    idx = 0;
    for(int i = 1; i <= cnt; i ++ ) 
    {
        son[i] = 0, siz[i] = 0;
        dep[i] = 0, fa[i] = 0;
        top[i] = 0;
    }
}

inline void solve()
{
    
    init();

    n = read(), m = read(), q = read();
    cnt = n;
    
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        ed[i] = {a, b, i};
    }

    Kru::kruskal();
    dfs1(rt, 0);
    dfs2(rt, rt);

    // for(int i = 1; i < n; i ++ ) cout << val[lca(i, i + 1)] << ' ';

    ST::init();

    while(q -- )
    {
        int l = read(), r = read();
        if(l == r) printf("0 ");
        else printf("%d ", ST::query(l, r - 1));
    }
    puts("");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    int T = read();
    while(T -- ) solve();

    return 0;
}
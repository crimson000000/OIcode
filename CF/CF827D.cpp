#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e5 + 10, INF = 0x3f3f3f3f;
struct edges
{
    int a, b, w, id;
    bool operator < (const edges& e) const
    {
        return w < e.w;
    }
}ed[N];

inline bool cmp(edges a, edges b)
{
    return a.id < b.id;
}

struct edge
{
    int v, w, id;
    edge(int _v, int _w, int _id): 
        v(_v), w(_w), id(_id) {}
};
vector<edge> G[N];
int n, m;

struct uniset
{
    int fa[N];
    inline void init()
    {
        for(int i = 1; i <= n; i ++ ) fa[i] = i;
    }

    inline int find(int x)
    {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }

    inline void merge(int x, int y)
    {
        x = find(x), y = find(y);
        fa[x] = y;
    }
}uni;

bitset<N> in_tree;
inline void kruskal()
{
    uni.init();
    sort(ed + 1, ed + m + 1);
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].w, id = ed[i].id;
        if(uni.find(a) == uni.find(b)) continue;
        G[a].emplace_back(b, c, id);
        G[b].emplace_back(a, c, id);
        in_tree[id] = true;
        uni.merge(a, b);
    }
}

int fa[N][21], f[N][21];
int dep[N];
int ans[N];
inline void dfs(int u, int fat)
{
    fa[u][0] = fat;
    dep[u] = dep[fat] + 1;
    for(auto e : G[u])
    {
        int v = e.v, w = e.w;
        if(v == fat) continue;
        // cout << v << ' ' << w << endl;
        f[v][0] = w;
        dfs(v, u);
    }
}

inline void init()
{
    for(int i = 1; i <= 19; i ++ )
        for(int u = 1; u <= n; u ++ )
        {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            f[u][i] = max(f[u][i - 1], f[fa[u][i - 1]][i - 1]);
        }
}

inline int querymax(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    int res = -INF;
    for(int i = 19; i >= 0; i -- )
        if(dep[fa[x][i]] >= dep[y])
        {
            res = max(res, f[x][i]);
            x = fa[x][i];
        }

    if(x == y) return res;

    for(int i = 19; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
        {
            res = max(res, f[x][i]);
            res = max(res, f[y][i]);
            x = fa[x][i];
            y = fa[y][i];
        }
    res = max(res, f[x][0]);
    res = max(res, f[y][0]);
    return res;
}

inline int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; i -- )
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];

    if(x == y) return x;

    for(int i = 19; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }

    return fa[x][0];
}

inline int kthfa(int x, int k)
{
    for(int i = 19; i >= 0; i -- )
        if(k >= (1 << i))
            x = fa[x][i], k -= (1 << i);
    return x;
}

int f1[N][21];
inline void cover(int x, int up, int w)
{
    if(x == up) return;
    int k = log2(dep[x] - dep[up]);
    f1[x][k] = min(f1[x][k], w);
    x = kthfa(x, dep[x] - dep[up] - (1 << k));
    f1[x][k] = min(f1[x][k], w);
    return;
}

inline void pushdown()
{
    for(int i = 19; i > 0; i -- )
        for(int u = 1; u <= n; u ++ )
        {
            f1[u][i - 1] = min(f1[u][i], f1[u][i - 1]);
            f1[fa[u][i - 1]][i - 1] = min(f1[fa[u][i - 1]][i - 1], f1[u][i]);
        }
}

inline void dfs_ans(int u, int fat)
{
    for(auto e : G[u])
    {
        int v = e.v, id = e.id;
        if(v == fat) continue;
        ans[id] = f1[v][0] - 1;
        dfs_ans(v, u);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(f1, 0x3f, sizeof f1);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        ed[i] = {a, b, c, i};
    }

    kruskal();
    sort(ed + 1, ed + m + 1, cmp);
    dfs(1, 0);
    init();

    // cout << f[6][0] << endl;

    for(int i = 1; i <= m; i ++ ) 
        if(!in_tree[i])
        {
            int a = ed[i].a, b = ed[i].b;
            ans[i] = querymax(a, b) - 1;
        }

    for(int i = 1; i <= m; i ++ )
        if(!in_tree[i])
        {
            int a = ed[i].a, b = ed[i].b, c = ed[i].w;
            int lc = lca(a, b);
            cover(a, lc, c);
            cover(b, lc, c);
        }
        // else cout << ed[i].a << ' ' << ed[i].b << ' ' << ed[i].w << endl;

    pushdown();
    // for(int i = 0; i < 3; i ++ )
    // {
    //     for(int u = 1; u <= n; u ++ )
    //         cout << f1[u][i] << ' ';
    //     puts("");
    // }

    dfs_ans(1, 1);

    for(int i = 1; i <= m; i ++ ) 
        printf("%d ", ans[i] == INF - 1 ? -1 : ans[i]);

    return 0;
}

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
int h[N], e[N], ne[N], w[N], idx;
set<int> H;
int n, m;
int a[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N], dist[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dist[v] = dist[u] + w[i];
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

namespace kth
{
    int son[N], maxdep[N];
    void dfs1(int u, int f)
    {
        maxdep[u] = dep[u];
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            dfs1(v, u);
            if(maxdep[v] > maxdep[u])
            {
                son[u] = v;
                maxdep[u] = maxdep[v];
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

    inline int kfa(int x, int k)
    {
        while(k)
        {
            if(dfn[x] - dfn[top[x]] < k)
            {
                k -= dfn[x] - dfn[top[x]] + 1;
                x = fa[top[x]];
            }
            else return anti[dfn[x] - k];
        }
        return x;
    }
}

namespace doubly
{
    int fa[N >> 1][20], dist[N >> 1][20];
    void dfs(int u, int f)
    {
        fa[u][0] = f;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            dist[v][0] = w[i];
            dfs1(v, u);
        }
    }

    void init()
    {
        for(int i = 1; i <= 18; i ++ )
            for(int u = 1; u <= n; u ++ )
            {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
                dist[u][i] = dist[u][i - 1] + dist[fa[u][i - 1]][i - 1];
            }
    }

    inline int jump(int x, int d)
    {
        for(int i = 18; i >= 0; i -- )
        {
            if(dist[x][i] <= d)
            {
                d -= dist[x][i];
                x = fa[x][i];
            }
        }
        return x;
    }
}

inline void init_all_in_one()
{
    dfs1(1, 1);
    dfs2(1, 1);
    kth::dfs1(1, 1);
    kth::dfs2(1, 1);
    doubly::dfs(1, 1);
    doubly::init();
}

struct node
{
    int i, s, rest;
};

bitset<N> st;
vector<node> ry;
vector<int> H;

void idontknowhowtonamethisfunction(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        
    }
}

inline bool check(int mid)
{
    st.reset();
    ry.clear();
    for(int i = 1; i <= m; i ++ )
    {
        int tp = kth::kfa(a[i], dep[a[i]] - 1);
        if(dist[u] - dist[tp] > mid) st[doubly::jump(u, mid)] = true;
        else 
        {
            ry.push_back({i, tp, mid - (dist[u] - dist[tp])});
            st[tp] = true;
        }
    }
    
    
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
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    init_all_in_one();

    m = read();
    for(int i = 1; i <= m; i ++ ) a[i] = read();

    int l = 0, r = 1e9;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << l << endl;

    return 0;
}
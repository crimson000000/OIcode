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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
vector<int> g[N];
int n, q;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace cn
{
    queue<int> q;
    bitset<N> st;

    inline void push(int u)
    {
        if(!st[u])
        {
            st[u] = true;
            q.push(u);
        }
    }

    inline void clear()
    {
        while(q.size())
        {
            int u = q.front();
            st[u] = false;
            g[u].clear();
            q.pop();
        }
    }
}

inline void aded(int a, int b)
{
    g[a].emplace_back(b);
    g[b].emplace_back(a);
    cn::push(a);
    cn::push(b);
}

//------------------------tree

int fa[N >> 1][20], dep[N];
int lg[N];
int siz[N], dfn[N], tim;
void dfs(int u, int f)
{
    dfn[u] = ++ tim;
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
}

void init()
{
    for(int i = 1; i <= 19; i ++ )
        for(int j = 1; j <= n; j ++ )
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
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
            x = fa[x][i], y = fa[y][i];
    
    return fa[x][0];
}

//------------------------
//------------------------Virtual Tree

int S[N], ans[N], tmp[N];
bitset<N> st;
int stk[N], tt;

inline bool cmp(int x, int y)
{
    return dfn[x] < dfn[y];
}

inline void insert(int u)
{
    int lc = lca(u, stk[tt]);
    while(tt > 1 && dep[lc] <= dep[stk[tt - 1]])
    {
        aded(stk[tt], stk[tt - 1]);
        tt --;
    }
    if(lc != stk[tt])
    {
        aded(lc, stk[tt]);
        stk[tt] = lc;
    }
    stk[++ tt] = u;
}

inline void build(int m)
{
    sort(S + 1, S + m + 1, cmp);
    stk[tt = 1] = S[1];

    for(int i = 2; i <= m; i ++ ) insert(S[i]);

    while(tt > 1) 
    {
        aded(stk[tt], stk[tt - 1]);
        tt --;
    }
}

//------------------------
//------------------------solve

int dp[N], f[N];

inline void calc(int x, int y)
{
    int p = y, q = y;
    for(int i = lg[dep[p]]; i >= 0; i -- )
        if(dep[fa[p][i]] > dep[x])
            p = fa[p][i];

    ans[f[x]] -= siz[p];

    for(int i = lg[dep[q]]; i >= 0; i -- )
    {
        int llen = dep[y] - dep[fa[q][i]] + dp[y];
        int rlen = dep[fa[q][i]] - dep[x] + dp[x];
        if(dep[fa[q][i]] > dep[x] && (llen < rlen || (llen == rlen && f[y] < f[x])))
            q = fa[q][i];
    }
    ans[f[y]] += siz[q] - siz[y];
    ans[f[x]] += siz[p] - siz[q];
}

void dfs1(int u, int fat)
{
    dp[u] = INF;
    for(auto v : g[u])
    {
        if(v == fat) continue;
        dfs1(v, u);
        if(dp[u] > dp[v] + dep[v] - dep[u]) 
        {
            dp[u] = dp[v] + dep[v] - dep[u];
            f[u] = f[v];
        }
        else if(dp[u] == dp[v] + dep[v] - dep[u])
            f[u] = min(f[u], f[v]);
    }
    if(st[u]) f[u] = u, dp[u] = 0;
}

void dfs2(int u, int fat)
{
    for(auto v : g[u])
    {
        if(v == fat) continue;
        int dis = dep[v] - dep[u];
        if(dp[u] + dis < dp[v])
        {
            dp[v] = dp[u] + dis;
            f[v] = f[u];
        }
        else if(dp[u] + dis == dp[v])
            f[v] = min(f[v], f[u]);
        calc(u, v);
        dfs2(v, u);
    }
    ans[f[u]] += siz[u];
    st[u] = false;
}

inline void solve(int m)
{
    cn::clear();
    build(m);
    dfs1(1, 0);
    dfs2(1, 0);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    lg[1] = 0;
    for(int i = 2; i <= 3e5; i ++ ) lg[i] = lg[i >> 1] + 1;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs(1, 0);
    init();

    q = read();
    while(q -- )
    {
        bool flag = true;
        int m = read();
        for(int i = 1; i <= m; i ++ )
        {
            S[i] = read();
            st[S[i]] = true;
            ans[S[i]] = 0;
        }

        if(!st[1]) S[++ m] = 1, flag = false;
        for(int i = 1; i <= m; i ++ ) tmp[i] = S[i];
        solve(m);

        for(int i = 1; i <= m; i ++ )
            if(tmp[i] != 1 || flag)
                printf("%d ", ans[tmp[i]]);
        puts("");
    }

    return 0;
}
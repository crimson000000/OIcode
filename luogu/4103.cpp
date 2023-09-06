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

const int N = 3e6 + 10, M = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f;
int h[N], e[N], ne[N], idx;
struct edge
{
    int v;
    ll w;
    edge(int _v, ll _w): v(_v), w(_w) {}
};
vector<edge> g[M];
int n, q;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace cn
{
    queue<int> bin;
    bitset<N> st;

    inline void push(int a)
    {
        if(!st[a])
        {
            st[a] = true;
            bin.push(a);
        }
    }

    inline void clear()
    {
        while(bin.size())
        {
            int u = bin.front();
            st[u] = false;
            g[u].clear();
            bin.pop();
        }
    }
}

inline void aded(int a, int b, ll c)
{
    g[a].emplace_back(edge(b, c));
    g[b].emplace_back(edge(a, c));
    cn::push(a);
    cn::push(b);
}

int fa[N], siz[N], son[N], dep[N];
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

int top[N], dfn[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
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

int S[N];
bitset<N> st;
int stk[N], tt;

inline int dis(int x, int y)
{
    return dep[x] + dep[y] - (dep[lca(x, y)] << 1);
}

inline bool cmp(int a, int b)
{
    return dfn[a] < dfn[b];
}

inline void insert(int u)
{
    int lc = lca(u, stk[tt]);
    while(tt > 1 && dep[stk[tt - 1]] >= dep[lc])
    {
        aded(stk[tt - 1], stk[tt], dis(stk[tt - 1], stk[tt]));
        tt --;
    }
    if(stk[tt] != lc) 
    {
        aded(stk[tt], lc, dis(stk[tt], lc));
        stk[tt] = lc;
    }
    stk[++ tt] = u;
}

namespace sv
{
    int siz[N];
    ll ans1, ans2, ans3;
    void init()
    {
        ans1 = ans2 = 0;
        ans3 = INF;
    }

    void dfs1(int u, int fat, int sz)
    {
        siz[u] = st[u] ? 1 : 0;
        for(auto e : g[u])
        {
            int v = e.v, w = e.w;
            if(v == fat) continue;
            dfs1(v, u, sz);
            siz[u] += siz[v];
            ans1 += (ll)w * siz[v] * (sz - siz[v]);
        }
    }

    ll f[N];
    void dfs2(int u, int fat)
    {
        f[u] = st[u] ? 0 : -INF;
        for(auto e : g[u])
        {
            int v = e.v, w = e.w;
            if(v == fat) continue;
            dfs2(v, u);
            ans2 = max(ans2, f[u] + f[v] + w);
            f[u] = max(f[u], f[v] + w);
        }
    }

    ll dp[N];
    void dfs3(int u, int fat)
    {
        dp[u] = st[u] ? 0 : INF;
        for(auto e : g[u])
        {
            int v = e.v, w = e.w;
            if(v == fat) continue;
            dfs3(v, u); 
            ans3 = min(ans3, dp[u] + dp[v] + w);
            dp[u] = min(dp[u], dp[v] + w);
        }
    }

    void KFC_family_bucket(int u, int sz)
    {
        init();
        dfs1(u, 0, sz);
        dfs2(u, 0);
        dfs3(u, 0);
        printf("%lld %lld %lld\n", ans1, ans3, ans2);
    }
}

inline void solve(int c)
{
    cn::clear();
    sort(S + 1, S + c + 1, cmp);
    stk[tt = 1] = S[1];
    for(int i = 2; i <= c; i ++ ) insert(S[i]);

    while(tt > 1) 
    {
        aded(stk[tt - 1], stk[tt], dis(stk[tt - 1], stk[tt]));
        tt --;
    }

    sv::KFC_family_bucket(S[1], c);
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

    dfs1(1, 1);
    dfs2(1, 1);

    q = read();
    while(q -- )
    {
        int k = read();
        for(int i = 1; i <= k; i ++ )
        {
            S[i] = read();
            st[S[i]] = true;
        }
        solve(k);
        for(int i = 1; i <= k; i ++ ) st[S[i]] = false;
    }

    return 0;
}
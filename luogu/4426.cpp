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

const int N = 1e6 + 10, mod = 998244353;
int h[N], e[N], ne[N], idx;
vector<int> G[N];
int St[N], Ed[N], CNT;
int vis[N];
int n, m;
ll ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void aded(int a, int b)
{
    G[a].emplace_back(b);
    G[b].emplace_back(a);
}

// -----------------树剖--------------------
int fa[N], siz[N], son[N], dep[N];
int dfn[N], tim;
inline void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    dfn[u] = ++ tim;
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        if(!dfn[v])
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if(siz[v] > maxsiz)
            {
                maxsiz = siz[v];
                son[u] = v;
            }
        }
        else if(dfn[v] < dfn[u])
        {
            St[++ CNT] = u; 
            Ed[CNT] = v;
            vis[u] = vis[v] = 1;
        }
    }
}

int top[N];
inline void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    vis[u] += vis[son[u]];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
        vis[u] += vis[v];
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

// -----------------树剖 end--------------------

// -----------------虚树--------------------

inline bool cmp(int x, int y)
{
    return dfn[x] < dfn[y];
}

int stk[N], tt;
int S[N], cnt;
inline void insert(int u)
{
    if(tt == 1 && u != 1)
    {
        stk[++ tt] = u;
        return;
    }
    int lc = lca(u, stk[tt]);
    if(lc == u) return;
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

inline void build()
{
    cnt = 0;
    for(int i = 1; i <= CNT; i ++ )
        S[++ cnt] = St[i], S[++ cnt] = Ed[i];
    sort(S + 1, S + cnt + 1, cmp);
    // cnt = unique(S + 1, S + cnt + 1) - S - 1;
    // for(int i = 1; i <= cnt; i ++ ) cout << S[i] << ' ';
    // puts("");
    stk[tt = 1] = 1;
    for(int i = 1; i <= cnt; i ++ ) insert(S[i]);
    while(tt > 1) 
    {
        aded(stk[tt], stk[tt - 1]);
        tt --;
    }
}

// -----------------虚树end--------------------

// -----------------DP--------------------

ll rev[N][2], k0[N][2], k1[N][2];
ll dp[N][2];

inline void getdp(int u, int fat)
{
    rev[u][0] = rev[u][1] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v] || v == fat) continue;
        getdp(v, u);
        rev[u][0] = rev[u][0] * (rev[v][0] + rev[v][1]) % mod;
        rev[u][1] = rev[u][1] * rev[v][0] % mod;
    }
}

inline void DP(int u, int x)
{
    dp[u][0] = dp[u][1] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa[u] || v == x) continue;
        // printf("%d %d\n", u, v);
        DP(v, u);
        dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]) % mod;
        dp[u][1] = dp[u][1] * dp[v][0] % mod;
    }
}

inline void Get(int u, int fat)
{
    int v = u;
    k0[u][0] = 1;
    k0[u][1] = 1;
    k1[u][0] = 1;
    while(fa[v] != fat)
    {
        DP(fa[v], v);
        ll r0 = k0[u][0], r1 = k0[u][1];
        k0[u][0] = (dp[fa[v]][0] * r0 % mod + dp[fa[v]][1] * k1[u][0] % mod) % mod;
        k0[u][1] = (dp[fa[v]][0] * r1 % mod + dp[fa[v]][1] * k1[u][1] % mod) % mod;
        k1[u][0] = dp[fa[v]][0] * r0 % mod;
        k1[u][1] = dp[fa[v]][0] * r1 % mod;
        // cout << fat << endl;
        v = fa[v];
    }
}

inline void init(int u, int fat)
{
    getdp(u, fat);
    S[++ cnt] = u;
    if(u != fat) Get(u, fat);
    for(auto v : G[u])
    {
        if(v == fat) continue;
        // cout << v << ' ' << u << endl;
        init(v, u);
    }
}

inline void realdp(int u, int fat)
{
    for(auto v : G[u])
    {
        if(v == fat) continue;
        realdp(v, u);
        dp[u][0] = dp[u][0] * ((k0[v][0] * dp[v][0] % mod + k0[v][1] * dp[v][1] % mod) % mod) % mod;
        dp[u][1] = dp[u][1] * ((k1[v][0] * dp[v][0] % mod + k1[v][1] * dp[v][1] % mod) % mod) % mod;
    }
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
        add(a, b), add(b, a);
    }

    dfs1(1, 1);

    memset(h, -1, sizeof h);
    idx = 0;

    for(int i = 1; i <= n; i ++ ) 
    {
        // cout << fa[i] << ' ';
        if(fa[i] != i)
            add(fa[i], i), add(i, fa[i]);
    }
    // puts("");

    dfs2(1, 1); 
    build();
    // cout << CNT << endl;

    // for(int i = 1; i <= n; i ++ )
    //     for(auto v : G[i])
    //         printf("%d %d\n", i, v);

    cnt = 0;
    init(1, 1);

    // for(int i = 1; i <= n; i ++ )
    //     printf("%lld %lld\n", rev[i][0], rev[i][1]);

    int up = 1 << CNT;
    for(int s = 0; s < up; s ++ )
    {
        for(int i = 1; i <= cnt; i ++ )
            dp[S[i]][0] = rev[S[i]][0], dp[S[i]][1] = rev[S[i]][1];
        for(int i = 1; i <= CNT; i ++ )
            if(s >> (i - 1) & 1)
                dp[St[i]][0] = 0, dp[Ed[i]][1] = 0;
            else dp[St[i]][1] = 0;
        realdp(1, 1);
        ans = (ans + dp[1][1] + dp[1][0]) % mod;
    }

    cout << ans << endl;

    return 0;
}
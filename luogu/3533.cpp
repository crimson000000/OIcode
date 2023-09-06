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

const int N = 2e6 + 10;
vector<int> G[N];
int n, m;
int din[N], field[N], cyc[N];
int fa[N][21];

queue<int> q;
inline void toposort()
{
    for(int i = 1; i <= n; i ++ )
        if(!din[i])
            q.push(i);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        int v = fa[u][0];
        din[v] --;
        if(!din[v]) q.push(v);
    }
}

int dep[N], stp[N], tot, len[N];
inline void dfs(int u, int fat, int rt, int d)
{
    dep[u] = d, field[u] = rt;
    for(auto v : G[u])
    {
        if(din[v] || v == fat) continue;
        dfs(v, u, rt, d + 1);
    }
}

inline void dfs1(int u, int id, int d)
{
    if(stp[u]) return;
    cyc[u] = id, stp[u] = d;
    len[id] ++;
    dfs1(fa[u][0], id, d + 1);
}

inline void init()
{
    for(int i = 1; i <= 19; i ++ )
        for(int u = 1; u <= n; u ++ )
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
}

inline int lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x, y);
    int tmp = dep[x] - dep[y];
    for(int i = 19; i >= 0; i -- )
        if(tmp >> i & 1)
            x = fa[x][i];
    
    if(x == y) return x;

    for(int i = 19; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    
    return fa[x][0];
}

inline bool check(int a, int b, int c, int d)
{
    if(max(a, b) != max(c, d)) return max(a, b) < max(c, d);
    if(min(a, b) != min(c, d)) return min(a, b) < min(c, d);
    return a >= b;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        G[x].emplace_back(i);
        fa[i][0] = x;
        din[x] ++;
    }

    toposort();

    for(int i = 1; i <= n; i ++ )
        if(din[i])
        {
            dfs(i, 0, i, 0);
            if(!stp[i]) dfs1(i, ++ tot, 1);
        }
    
    init();

    // cout << lca(11, 8) << endl;

    while(m -- )
    {
        int a = read(), b = read();
        if(cyc[field[a]] != cyc[field[b]]) printf("-1 -1\n");
        else if(field[a] == field[b])
        {
            int lc = lca(a, b);
            printf("%d %d\n", dep[a] - dep[lc], dep[b] - dep[lc]);
        }
        else
        {
            int rt1 = field[a], rt2 = field[b];
            int c = cyc[rt1];
            int ans1 = dep[a] + (stp[rt2] - stp[rt1] + len[c]) % len[c];
            int ans2 = dep[b] + (stp[rt1] - stp[rt2] + len[c]) % len[c];
            if(check(dep[a], ans2, ans1, dep[b])) printf("%d %d\n", dep[a], ans2);
            else printf("%d %d\n", ans1, dep[b]);
        }
    }

    return 0;
}

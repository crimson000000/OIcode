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

using PII = pair<ll, ll>;

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int inf;
// f1 is max, f2 is min
int f1[N][20], f2[N][20];
int h[N], e[N], ne[N], idx;
int lg2[N];
int n, m;
unordered_map<int, int> id;
int quer[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void change1(int l, int r, int v)
{
    if(l > r) return;
    int k = lg2[r - l + 1];
    f1[l][k] = min(f1[l][k], v);
    f1[r - (1 << k) + 1][k] = min(f1[r - (1 << k) + 1][k], v);
}

inline void change2(int l, int r, int v)
{
    if(l > r) return;
    int k = lg2[r - l + 1];
    f2[l][k] = max(f2[l][k], v);
    f2[r - (1 << k) + 1][k] = max(f2[r - (1 << k) + 1][k], v);
}

inline void pushdown()
{
    for(int i = 17; i >= 0; i -- )
        for(int j = 1; j + (1 << (i + 1)) - 1 <= n; j ++ )
        {
            f1[j][i] = min(f1[j][i], f1[j][i + 1]);
            f1[j + (1 << i)][i] = min(f1[j + (1 << i)][i], f1[j][i + 1]);
            f2[j][i] = max(f2[j][i], f2[j][i + 1]);
            f2[j + (1 << i)][i] = max(f2[j + (1 << i)][i], f2[j][i + 1]);
        }
}



int fa[N], siz[N], son[N], dep[N];
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

int dfn[N], top[N], anti[N], tim;
inline void dfs2(int u, int t)
{
    dfn[u] = ++ tim;
    anti[tim] = u;
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

int L[N], R[N];
inline void init()
{
    for(int i = 2; i <= n; i ++ )
    {
        L[i] = f2[dfn[i]][0];
        R[i] = f1[dfn[i]][0];
    }
}

inline void maxchain(int x, int y, int v)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change1(dfn[top[x]], dfn[x], v);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    change1(dfn[y] + 1, dfn[x], v);
}

inline void minchain(int x, int y, int v)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        change2(dfn[top[x]], dfn[x], v);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    change2(dfn[y] + 1, dfn[x], v);
}

namespace Flow
{
    int h[N], e[N << 1], ne[N << 1], w[N << 1], idx;
    int now[N];
    int s, t;
    int flow, maxflow;
    
    inline void add(int a, int b, int c)
    {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
        e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
    }

    queue<int> q;
    int d[N];
    inline bool bfs()
    {
        while(q.size()) q.pop();
        for(int i = 1; i <= t; i ++ ) d[i] = 0;

        q.push(s);
        d[s] = 1;
        now[s] = h[s];

        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = h[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(w[i] && !d[v])
                {
                    d[v] = d[u] + 1;
                    now[v] = h[v];
                    q.push(v);
                    if(v == t) return true;
                }
            }
        }
        return false;
    }

    inline int dinic(int u, int flow)
    {
        if(u == t) return flow;
        int k, rest = flow;
        for(int i = now[u]; i != -1 && rest; i = ne[i])
        {
            now[u] = i;
            int v = e[i];
            if(w[i] && d[v] == d[u] + 1)
            {
                k = dinic(v, min(w[i], rest));
                if(!k) d[v] = 0;
                w[i] -= k;
                w[i ^ 1] += k;
                rest -= k;
            }
        }
        return flow - rest;
    }

    inline void solve()
    {
        memset(h, -1, sizeof h);
        s = n + m + 1, t = n + m + 2;
        for(int i = 2; i <= n; i ++ )
        {
            if(L[i] != inf) add(i, id[L[i]] + n, 1);
            if(R[i] != INF) add(i, id[R[i]] + n, 1);
        }

        for(int i = 2; i <= n; i ++ ) add(s, i, 1);
        for(int i = 1; i <= m; i ++ ) add(i + n, t, 1);
        
        while(bfs())
            while(flow = dinic(s, INF))
                maxflow += flow;

        // cout << maxflow << endl;

        for(int u = 2; u <= n; u ++ )
        {
            bool flag = false;
            for(int i = h[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(v == s) continue;
                if(w[i]) continue;
                v -= n;
                printf("%d %d %d\n", fa[u], u, quer[v]);
                flag = true;
            }
            if(!flag) 
                printf("%d %d %d\n", fa[u], u, R[u]);
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
    memset(f1, 0x3f, sizeof f1);
    memset(f2, -0x3f, sizeof f2);
    inf = f2[0][0];
    n = read();

    lg2[1] = 0;
    for(int i = 2; i <= n; i ++ ) lg2[i] = lg2[i >> 1] + 1;
    
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        char op[2];
        scanf("%s", op);
        int x = read(), y = read(), v = read();
        if(op[0] == 'm') minchain(x, y, v);
        else maxchain(x, y, v);
        id[v] = i;
        quer[i] = v;
    }

    pushdown();
    init();

    // for(int i = 2; i <= n; i ++ ) 
    //     printf("%d: [%d %d]\n", i, L[i], R[i]);

    Flow::solve();

    return 0;
} 
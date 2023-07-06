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

const int N = 2e6 + 10;

int n, m;

// public
queue<int> q;
bitset<N> vis;

// diameter
int st, ed;
int maxv, maxd;
int d[N];

struct Graph
{
    int h[N], e[N], ne[N], idx;
    int dist[N];
    int rt;

    void init()
    {
        memset(h, -1, sizeof h);
    }

    inline void add(int a, int b)
    {
        e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    }
    
    void bfs(int t)
    {
        vis.reset();
        maxd = -1;
        q.push(t);
        vis[t] = true;
        d[t] = 0;
        while(q.size())
        {
            int u = q.front();
            q.pop();

            if(d[u] > maxd)
            {
                maxd = d[u];
                maxv = u;
            }

            for(int i = h[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(vis[v]) continue;
                vis[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    inline void make_root(int x)
    {
        vis.reset();
        rt = x;
        q.push(x);
        dist[x] = 0;
        vis[x] = true;
        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = h[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(vis[v]) continue;
                dist[v] = dist[u] + 1;
                vis[v] = true;
                q.push(v);
            }
        }
    }

    int fa[N], dep[N], son[N], maxdep[N];
    void dfs1(int u, int f)
    {
        fa[u] = f, maxdep[u] = dep[f] + 1;
        dep[u] = dep[f] + 1;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            dfs1(v, u);
            if(maxdep[v] > maxdep[u])
            {
                maxdep[u] = maxdep[v];
                son[u] = v;
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
            int v = e[i];
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    inline void getchain()
    {
        dfs1(rt, rt);
        dfs2(rt, rt);
    }

    inline int kthfa(int u, int k)
    {
        while(k)
        {
            if(dep[u] - dep[top[u]] < k)
            {
                k -= dep[u] - dep[top[u]] + 1;
                u = fa[top[u]];
            }
            else return anti[dfn[u] - k];
        }
        return u;
    }
}g1, g2;


namespace diameter
{
    void main()
    {
        g1.bfs(1); st = maxv;
        g1.bfs(st); ed = maxv;

        g1.make_root(st);
        g2.make_root(ed);

        g1.getchain();
        g2.getchain();
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    g1.init(), g2.init();

    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        g1.add(a, b), g1.add(b, a);
        g2.add(a, b), g2.add(b, a);
    }

    diameter::main();

    // for(int i = 1; i <= n; i ++ )
    //     printf("%d: %d\n", i, g1.dist[i]);

    m = read();
    while(m -- )
    {
        int x = read(), k = read();
        if(g1.dist[x] < k && g2.dist[x] < k) puts("-1");
        else
        {
            if(g1.dist[x] >= k) printf("%d\n", g1.kthfa(x, k));
            else printf("%d\n", g2.kthfa(x, k));
        }
    }

    return 0;
}
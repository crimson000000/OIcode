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

const int N = 1e6 + 10, INF = 0x3f3f3f3f, M = 510;
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int g[M][M], p[M], t[M], v[N];
int n, m, k;
int maxflow, flow;
int S, T;

struct Union
{
    int p[N];

    void init(int n)
    {
        for(int i = 1; i <= n; i ++ ) p[i] = i;
    }

    int find(int a)
    {
        if(p[a] != a) p[a] = find(p[a]);
        return p[a];
    }

    void merge(int x, int y)
    {
        int pa = find(x), pb = find(y);
        if(pa == pb) return;
        p[pa] = p[pb];
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
} u;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

inline int get(int p, int time)
{
    return p + time * (n + 3);
}

queue<int> q;
bool bfs()
{
    memset(d, 0, sizeof d);
    while(q.size()) q.pop();
    q.push(S);
    d[S] = 1;
    now[S] = h[S];
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
                if(v == T) return true;
            }
        }
    }
    return false;
}

int dinic(int u, int flow)
{
    if(u == T) return flow;
    int rest = flow, k, i;
    for(i = now[u]; i != -1; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && d[v] == d[u] + 1)
        {
            k = dinic(v, min(rest, w[i]));
            if(!k) d[v] = 0;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), k = read();
    u.init(n + 5);
    for(int i = 1; i <= m; i ++ )
    {
        v[i] = read();
        p[i] = read();
        for(int j = 0; j < p[i]; j ++ )
        {
            g[i][j] = read();
            if(g[i][j] == 0) g[i][j] = n + 1;
            if(g[i][j] == -1) g[i][j] = n + 2;
            if(j != 0) u.merge(g[i][j], g[i][j - 1]);
        }
    }

    if(!u.same(n + 1, n + 2))
    {
        puts("0");
        return 0;
    }

    S = N - 5, T = N - 4;

    int ans = 1;
    add(S, get(n + 1, 0), INF);
    add(get(n + 2, 0), T, INF);
    for(; ; ans ++ )
    {
        for(int i = 1; i <= m; i ++ )
        {
            t[i] = ans % p[i];
            if(t[i] != 0) add(get(g[i][t[i] - 1], ans - 1), get(g[i][t[i]], ans), v[i]);
            else add(get(g[i][p[i] - 1], ans - 1), get(g[i][0], ans), v[i]);
        }

        for(int i = 1; i <= n + 2; i ++ )
            add(get(i, ans - 1), get(i, ans), INF);
        
        add(S, get(n + 1, ans), INF);
        add(get(n + 2, ans), T, INF);

        while(bfs())
            while(flow = dinic(S, INF))
                maxflow += flow;
        
        if(maxflow >= k) break;
    }

    cout << ans << endl;

    return 0;
}

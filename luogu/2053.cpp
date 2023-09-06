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

const int N = 1e6 + 10, M = 110, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N], now[N];
bitset<N> st;
int tim[M][M];
int ID[M][M], cnt;
int m, n, s, t;
int maxflow, flow, fee;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bool spfa()
{
    while(q.size()) q.pop();
    memset(dist, 0x3f, sizeof dist);
    st.reset();
    dist[s] = dist[t] = INF;
    q.push(s);
    dist[s] = 0;
    now[s] = h[s];
    st[s] = true;

    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + cost[i] && w[i])
            {
                dist[v] = dist[u] + cost[i];
                now[v] = h[v];
                if(!st[v])
                {
                    q.push(v);
                    st[v] = true;
                }
            }
        }
    }
    return dist[t] < INF / 2;
}

bitset<N> vis;
int nxt[N], top[N];
int dinic(int u, int flow)
{
    if(u == t) return flow;
    int i, k, rest = flow;
    vis[u] = true;
    for(i = now[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        now[u] = i;
        if(w[i] && dist[v] == dist[u] + cost[i] && !vis[v])
        {
            k = dinic(v, min(w[i], rest));
            if(!k) dist[v] = INF;
            w[i] -= k;
            w[i ^ 1] += k;
            fee += cost[i] * k;
            rest -= k;
            if(k) nxt[u] = v;
        }
    }
    vis[u] = false;
    return flow - rest;
}


int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    m = read(), n = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            tim[i][j] = read();
    
    cnt = n;
    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= n; j ++ )
            ID[i][j] = ++ cnt;
    
    s = ++ cnt;
    t = ++ cnt;

    for(int i = 1; i <= n; i ++ ) add(s, i, 1, 0);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            for(int u = 1; u <= n; u ++ )
                add(i, ID[j][u], 1, u * tim[i][j]);
        
    for(int i = n + 1; i <= cnt - 2; i ++ )
        add(i, t, 1, 0);

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    printf("%.2lf\n", (double)fee / n);

    return 0;
}
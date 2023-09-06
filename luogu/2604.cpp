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

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N >> 1], now[N];
int n, m, k, s, t;
int flow, maxflow, fee;
struct edge
{
    int a, b, c, d;
}edge[N];

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bitset<N> st;
inline bool spfa()
{
    memset(dist, 0x3f, sizeof dist);
    q.push(s);
    st[s] = true;
    now[s] = h[s];
    dist[s] = 0;

    while(q.size())
    {
        int u = q.front();
        st[u] = false;
        q.pop();

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
    return dist[t] < INF;
}

bitset<N> vis;
int dinic(int u, int flow)
{
    if(u == t) return flow;
    vis[u] = true;
    int k, rest = flow;
    for(int i = now[u]; i != -1 && rest; i = ne[i])
    {
        int v = e[i];
        now[u] = i;
        if(w[i] && dist[v] == dist[u] + cost[i] && !vis[v])
        {
            k = dinic(v, min(rest, w[i]));
            if(!k) dist[v] = INF;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
            fee += cost[i] * k;
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

    n = read(), m = read(), k = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read(), d = read();
        add(a, b, c, 0);
        edge[i] = {a, b, c, d};
    }

    s = 1, t = n;
    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << maxflow << ' ';

    for(int i = 1; i <= m; i ++ )
    {
        int a = edge[i].a, b = edge[i].b, c = edge[i].c, d = edge[i].d;
        add(a, b, INF, d);
    }

    add(0, 1, k, 0);
    s = 0, t = n;
    fee = 0, flow = 0, maxflow = 0;
    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << fee << endl;

    return 0;
}
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

const int N = 1e6 + 10, M = 1010, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N], now[N];
int tim[M][M], f[M][M];
int in[N], out[N], cnt;
struct request
{
    int a, b, s, t, c;
}q[N];
int n, m, k, T;
int s, t, s1;
int maxflow, flow, fee;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> qq;
bitset<N> st;
bool spfa()
{
    for(int i = 1; i <= cnt; i ++ ) dist[i] = -INF;
    st.reset();
    qq.push(s);
    dist[s] = 0;
    st[s] = true;
    now[s] = h[s];
    while(qq.size())
    {
        int u = qq.front();
        qq.pop();
        st[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] < dist[u] + cost[i] && w[i])
            {
                dist[v] = dist[u] + cost[i];
                now[v] = h[v];
                if(!st[v])
                {
                    qq.push(v);
                    st[v] = true;
                }
            }
        }
    }
    return dist[t] > -10000;
}

bitset<N> vis;
int dinic(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, k, i;
    vis[u] = true;
    for(i = now[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(dist[v] == dist[u] + cost[i] && w[i] && !vis[v])
        {
            k = dinic(v, min(rest, w[i]));
            if(!k) dist[v] = -INF;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
            fee += k * cost[i];
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

    n = read(), m = read(), k = read(), T = read();
    t = ++ cnt;
    s = ++ cnt;
    s1 = ++ cnt;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            tim[i][j] = read();
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            f[i][j] = read();
    
    for(int i = 1; i <= m; i ++ )
    {
        int a = read() + 1, b = read() + 1, s = read(), t = read(), c = read();
        q[i] = {a, b, s, t, c};
        in[i] = ++ cnt;
        out[i] = ++ cnt;
    }

    for(int i = 1; i <= m; i ++ )
    {
        add(in[i], out[i], 1, q[i].c);
        if(q[i].t + tim[q[i].b][1] <= T) add(out[i], t, INF, -f[q[i].b][1]);
        else continue;
        if(q[i].s >= tim[1][q[i].a]) add(s1, in[i], INF, -f[1][q[i].a]);
    }

    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= m; j ++ )
            if(q[i].t + tim[q[i].b][q[j].a] <= q[j].s)
                add(out[i], in[j], INF, -f[q[i].b][q[j].a]);

    add(s, s1, k, 0);
    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << fee << endl;

    return 0;
}

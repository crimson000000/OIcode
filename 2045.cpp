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
const int dx[] = {1, 0}, dy[] = {0, 1};
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N], now[N];
int in[M][M], out[M][M], cnt;
int a[M][M];
int n, k, s, t;
int maxflow, flow, fee;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bool st[N];
bool spfa()
{
    for(int i = 1; i <= cnt; i ++ ) dist[i] = -INF, st[i] = 0;
    dist[s] = dist[t] = -INF;
    st[s] = st[t] = 0;
    while(q.size()) q.pop();
    q.push(s);
    dist[s] = 0;
    st[s] = true;
    now[s] = h[s];
    while(q.size())
    {
        int u = q.front();
        q.pop();
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
                    q.push(v);
                    st[v] = true;
                }
            }
        }
    }
    return dist[t] > 0;
}

bitset<N> vis;
int dinic(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, k, i;
    vis[u] = true;
    for(i = now[u]; i != -1; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(dist[v] == dist[u] + cost[i] && w[i] && !vis[v])
        {
            k = dinic(v, min(w[i], rest));
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

    n = read(), k = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            in[i][j] = ++ cnt;
            out[i][j] = ++ cnt;
        }

    s = in[1][1], t = out[n][n];

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            a[i][j] = read();
            for(int u = 1; u <= k; u ++ )
            {
                if(u == 1) add(in[i][j], out[i][j], 1, a[i][j]);
                else add(in[i][j], out[i][j], 1, 0);
            }
        }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            for(int k = 0; k < 2; k ++ )
            {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || x > n || y < 1 || y > n) continue;
                add(out[i][j], in[x][y], INF, 0);
            }

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << fee << endl;

    return 0;
}
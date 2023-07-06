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

const int N = 1e6 + 10, M = 50, INF = 0x3f3f3f3f;
const int dx[] = {0, 1}, dy[] = {1, 0};
int h[N], e[N], ne[N], w[N], cost[N], idx;
int now[N], dist[N];
int mp[M][M], in[M][M], out[M][M], cnt;
bitset<N> cant;
PII point[N];
int n, m, k;
int s, t;
int maxflow, flow, fee;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bitset<N> st;
inline bool spfa()
{
    memset(dist, -0x3f, (3 * n * m + 10) * sizeof(int));
    dist[t] = -INF;
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
            if(w[i] && dist[v] < dist[u] + cost[i])
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
    return dist[t] > -INF / 2;
}

bitset<N> vis;
int dinic(int u, int flow)
{
    if(u == t) return flow;
    vis[u] = true;
    int k, rest = flow;
    for(int i = now[u]; i != -1 && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(!vis[v] && w[i] && dist[v] == dist[u] + cost[i])
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

inline int ID(int x, int y)
{
    return (x - 1) * m + y;
}

void print(int id, int u)
{
    int tmp = u - 2 * n * m;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(!w[i]) continue;
        int to = v - 2 * n * m;
        if(tmp + 1 == to) printf("%d 1\n", id);
        else printf("%d 0\n", id);
        w[i] --;
        print(id, v);
        break;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    k = read(), m = read(), n = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            mp[i][j] = read();
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            in[i][j] = ++ cnt;
            out[i][j] = in[i][j] + n * m;
        }

    s = N - 3, t = N - 2;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j] == 0) add(in[i][j], out[i][j], INF, 0);
            if(mp[i][j] == 2) add(in[i][j], out[i][j], 1, 1), add(in[i][j], out[i][j], INF, 0);
            if(mp[i][j] == 1) cant[in[i][j]] = true;
            for(int k = 0; k < 2; k ++ )
            {
                int a = i + dx[k], b = j + dy[k];
                if(a < 1 || a > n || b < 1 || b > m) continue;
                add(out[i][j], in[a][b], INF, 0);
            }
        }

    add(s, in[1][1], k, 0);
    add(out[n][m], t, k, 0);

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;

    // cout << fee << endl;
    
    for(int x = n * m + 1; x <= 2 * n * m; x ++ )
    {
        if(cant[x - n * m]) continue;
        for(int i = h[x]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(cant[v]) continue;
            if(v + n * m == x) continue;
            if(w[i] == INF) continue;
            if(v != t) add(x + n * m, v + 2 * n * m, INF - w[i], 0);
        }
    }

    for(int i = 1; i <= k; i ++ )
        print(i, 1 + 2 * n * m);

    return 0;
}
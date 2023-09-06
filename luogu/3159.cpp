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

const int N = 1e5 + 10, M = 25, INF = 0x3f3f3f3f;
const int dx[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int dy[] = {1, 0, -1, -1, -1, 0, 1, 1};
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N], now[N];
int mp[M][M], goal[M][M], tot[M][M];
char c[M];
int in[M][M], out[M][M], cnt;
int n, m, s, t;
int flow, maxflow, fee, fans;

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
            if(dist[v] > dist[u] + cost[i] && w[i])
            {
                now[v] = h[v];
                dist[v] = dist[u] + cost[i];
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
int dinic(int u, int flow)
{
    if(u == t) return flow;
    vis[u] = true;
    int rest = flow, k;
    for(int i = now[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        now[u] = i;
        if(dist[v] == dist[u] + cost[i] && w[i] && !vis[v])
        {
            k = dinic(v, min(w[i], rest));
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

int cnt1, cnt2;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            in[i][j] = ++ cnt;
            out[i][j] = ++ cnt;
        }

    s = ++ cnt, t = ++ cnt;

    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%s", c + 1);
        for(int j = 1; j <= m; j ++ )
            mp[i][j] = c[j] - '0';
    }

    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%s", c + 1);
        for(int j = 1; j <= m; j ++ )
            goal[i][j] = c[j] - '0';
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j]) cnt1 ++;
            if(goal[i][j]) cnt2 ++;

            if(mp[i][j] && !goal[i][j])
                add(s, in[i][j], 1, 0), fans ++;
            if(!mp[i][j] && goal[i][j])
                add(out[i][j], t, 1, 0);
        } 
    
    if(cnt1 != cnt2)
    {
        puts("-1");
        return 0;
    }

    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", c + 1);
        for(int j = 1; j <= m; j ++ )
        {
            tot[i][j] = c[j] - '0';
            int cnt = tot[i][j];
            add(in[i][j], out[i][j], cnt >> 1, 0);
            if((mp[i][j] ^ goal[i][j]) && (cnt & 1))
                add(in[i][j], out[i][j], 1, 0);
            for(int u = 0; u < 8; u ++ )
            {
                int a = i + dx[u], b = j + dy[u];
                if(a < 1 || a > n || b < 1 || b > m) continue;
                add(out[i][j], in[a][b], INF, 1);
            }
        }
        
    }

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    if(maxflow != fans) 
    {
        puts("-1");
        return 0;
    }
    cout << fee << endl;

    return 0;
}
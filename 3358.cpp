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
int dist[N], now[N];
int in[N], out[N], cnt;
struct seg
{
    int l, r, len;
}p[N];
vector<int> nums;
int n, k, s, t, ss;
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
    memset(dist, -0x3f, sizeof dist);
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
        if(w[i] && !vis[v] && dist[v] == dist[u] + cost[i])
        {
            k = dinic(v, min(w[i], rest));
            if(!k) dist[v] = -INF;
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

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ )
    {
        int l = read(), r = read();
        p[i] = {l, r, r - l};
        in[i] = ++ cnt;
        out[i] = ++ cnt;
    }
    
    s = ++ cnt;
    t = ++ cnt;
    ss = ++ cnt;
    
    add(s, ss, k, 0);

    for(int i = 1; i <= n; i ++ )
    {
        add(ss, in[i], 1, 0);
        add(out[i], t, 1, 0);
        add(in[i], out[i], 1, p[i].len);
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = i + 1; j <= n; j ++ )
        {
            if(p[i].r <= p[j].l) add(out[i], in[j], INF, 0);
            else if(p[j].r <= p[i].l) add(out[j], in[i], INF, 0);
        }
    
    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << fee << endl;

    return 0;
}
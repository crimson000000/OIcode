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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], cost[N], idx;
int dist[N], now[N];
int n, m, s, t;
int flow, maxflow;
int fee;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Q
{
    int q[N];
    int hh = 0, tt = -1;

    inline void init() {hh = 0, tt = -1;}
    inline void push(int val) { q[++ tt] = val;}
    inline bool empty() {return hh > tt;};
    inline int front() {return q[hh]; }
    inline void pop() {hh ++ ;}
}q;

bitset<N> st;
inline bool spfa()
{
    for(int i = 1; i <= n; i ++ ) dist[i] = INF;
    dist[s] = 0;
    q.init();
    q.push(s);
    st[s] = true;
    now[s] = h[s];
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        st[u] = false;
        for(int i = h[u]; ~i; i = ne[i])
        {
            int v = e[i];
            if(!w[i]) continue;
            if(dist[v] > dist[u] + cost[i])
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
inline int dinic(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, k, i;
    vis[u] = true;
    for(i = now[u]; (~i) && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && !vis[v] && dist[v] == dist[u] + cost[i])
        {
            k = dinic(v, min(rest, w[i]));
            if(!k) dist[v] = INF;
            w[i] -= k;
            w[i ^ 1] += k;
            fee += k * cost[i];
            rest -= k; 
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

    n = read(), m = read(), s = read(), t = read();
    while(m -- )
    {
        int a = read(), b = read(), c = read(), d = read();
        add(a, b, c, d);
    }

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << maxflow << ' ' << fee << endl;

    return 0;
}

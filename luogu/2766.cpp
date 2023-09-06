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
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int in[N], out[N];
int n, k, s, t, cnt;
int a[N];
int f[N];
int maxflow, flow;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bool bfs()
{
    memset(d, 0, sizeof d);
    while(q.size()) q.pop();
    q.push(s);
    d[s] = 1;
    now[s] = h[s];
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(!d[v] && w[i])
            {
                now[v] = h[v];
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return true;
            }
        }
    }
    return false;
}

int dinic(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, i, k;
    for(i = h[u]; i != -1 && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(d[v] == d[u] + 1 && w[i])
        {
            k = dinic(v, min(rest, w[i]));
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

    n = read();
    if(n == 1)
    {
        printf("1\n1\n1\n");
        return 0;
    }

    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ )
    {
        f[i] = 1;
        for(int j = 1; j < i; j ++ )
            if(a[j] <= a[i]) 
                f[i] = max(f[i], f[j] + 1);
        k = max(k, f[i]);
    }

    cout << k << endl;
    
    s = 0, t = N - 2;
    cnt = 1;

    for(int i = 1; i <= n; i ++ )
    {
        in[i] = ++ cnt;
        out[i] = ++ cnt;
        add(in[i], out[i], 1);
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(f[i] == 1) add(s, in[i], 1);
        if(f[i] == k) add(out[i], t, 1);
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = i + 1; j <= n; j ++ )
            if(f[j] == f[i] + 1 && a[i] <= a[j])
            {
                add(out[i], in[j], 1);
            }
    
    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << maxflow << endl;

    add(in[1], out[1], INF);
    add(s, in[1], INF);
    if(f[n] == k)
    { 
        add(in[n], out[n], INF);
        add(out[n], t, INF);
    }

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << maxflow << endl;

    return 0;
}
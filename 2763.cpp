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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int n, m, k;
int s, t;
int flow, maxflow;

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
            if(w[i] && !d[v])
            {
                d[v] = d[u] + 1;
                q.push(v);
                now[v] = h[v];
                if(v == t) return true;
            }
        }
    }
    return false;
}

int dinic(int x, int flow)
{
    if(x == t) return flow;
    int rest = flow, k, i;
    for(i = now[x]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(w[i] && d[v] == d[x] + 1)
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

    k = read(), n = read();
    for(int i = 1; i <= k; i ++ )
    {
        int x = read();
        m += x;
        add(s, i + n, x);
    }

    t = N - 2;
    for(int i = 1; i <= n; i ++ )
    {
        int p = read();
        while(p -- )
        {
            int x = read();
            add(x + n, i, 1);
        }
    }

    for(int i = 1; i <= n; i ++ ) add(i, t, 1);

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;

    if(maxflow != m) 
    {
        puts("No Solution!");
        return 0;
    }

    for(int i = 1; i <= k; i ++ )
    {
        printf("%d: ", i);
        int p = i + n;
        for(int i = h[p]; i != -1; i = ne[i])
        {
            if(!w[i] && e[i] != s && e[i] != t) printf("%d ", e[i]);
        }
        puts("");
    }
    
    return 0;
}

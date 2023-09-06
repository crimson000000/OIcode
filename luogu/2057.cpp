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
int n, m, s, t;
int maxflow, flow;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bool bfs()
{
    for(int i = 0; i <= n; i ++ ) d[i] = 0;
    d[t] = 0;
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
                now[v] = h[v];
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
    int rest = flow, k, i;
    for(i = now[u]; i != -1; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && d[v] == d[u] + 1)
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

    n = read(), m = read();
    s = 0, t = N - 5;

    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        if(x == 0) add(s, i, 1);
        else add(i, t, 1);
    }

    while(m -- )
    {
        int a = read(), b = read();
        add(a, b, 1), add(b, a, 1);
    }

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << maxflow << endl;

    return 0;
}
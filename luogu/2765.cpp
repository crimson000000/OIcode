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

const int N = 1e6 + 10, INF = 0x3f3f3f3f, M = 1e5 + 10;
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int squ[N], to[N];
bool pb[N];
int n;
int s, t;

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
        if(d[v] == d[u] + 1 && w[i])
        {
            k = dinic(v, min(w[i], rest));
            if(!k) d[v] = 0;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int dinic()
{
    int maxflow = 0, flow = 0;
    while(bfs())
        while(flow = dinic(s, INF));
            maxflow += flow;
    return maxflow;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= 4000; i ++ ) squ[i] = i * i;
    s = N - 3, t = N - 2;

    int num = 1, sum = 0;
    
    while(1)
    {
        int k = lower_bound(squ + 1, squ + 1000, num) - squ;
        add(s, num, 1), add(num + M, t, 1);
        for(int j = 2 * k; j; j -- )
        {
            int u = squ[j] - num;
            if(u > 0 && u < num) 
            {
                add(u, num + M, 1);
            }
        }
        // sum += dinic();
        int flow = 0;
        while(bfs())
            while(flow = dinic(s, INF))
                sum += flow;

        if(num - sum > n) break;
        num ++;
    }

    printf("%d\n", num - 1);
    for(int u = 1; u < num; u ++ )
        for(int i = h[u]; i != -1; i = ne[i])
            if(!w[i] && e[i] != s && e[i] != t)
            {
                to[u] = e[i] - M; 
                break;
            }

    for(int i = 1; i < num; i ++ )
    {
        if(pb[i]) continue;
        for(int j = i; j > 0; j = to[j])
        {
            pb[j] = true;
            cout << j << ' ';
        }
        puts("");
    }

    return 0;
}
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

const int N = 1e6 + 10, M = 110, INF = 0x3f3f3f3f;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int mp[M][M];
int n, m, s, t;
ll maxflow, flow;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

inline int get(int x, int y)
{
    return (x - 1) * m + y;
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

int dinic(int u, int flow)
{
    if(u == t) return flow;
    int rest = flow, k, i;
    for(i = now[u]; i != -1 && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && d[v] == d[u] + 1)
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    s = N - 3, t = N - 2;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            mp[i][j] = read();
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ ) 
            if(mp[i][j] == 1)
                add(s, get(i, j), INF);
            else if(mp[i][j] == 2)
                add(get(i, j), t, INF);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            for(int k = 0; k < 4; k ++ )
            {
                int x = i + dx[k], y = j + dy[k];
                if(x >= 1 && x <= n && y >= 1 && y <= m) 
                    add(get(i, j), get(x, y), 1);
            }
    
    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << maxflow << endl;

    return 0;
}

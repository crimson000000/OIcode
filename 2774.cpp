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

const int N = 1e6 + 10, INF = 0x3f3f3f3f, M = 1010;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int id[M][M], cnt;
int a[M][M];
int n, m, s, t, sum;
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

    s = N - 4, t = N - 3;

    m = read(), n = read();
    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= n; j ++ )
            id[i][j] = ++ cnt;

    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            a[i][j] = read();
            sum += a[i][j];
            if(!((i + j) & 1)) add(id[i][j], t, a[i][j]);
            else 
            {
                add(s, id[i][j], a[i][j]);
                for(int k = 0; k < 4; k ++ )
                {
                    int x = i + dx[k], y = j + dy[k];
                    if(x < 1 || x > m || y < 1 || y > n) continue;
                    add(id[i][j], id[x][y], INF);
                }
            }
        }

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << sum - maxflow << endl;

    return 0;
}

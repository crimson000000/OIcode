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

const int N = 1e6 + 10, M = 510, INF = 0x3f3f3f3f;
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
bool dang[M][M];
int flow, maxflow;
int s, t;
int n, m, cnt;
int id[M][M];

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
        if(d[v] == d[u] + 1 && w[i])
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

    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read();
        dang[x][y] = true;
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            id[i][j] = ++ cnt;

    s = ++ cnt; t = ++ cnt;

    for(int x = 1; x <= n; x ++ )
        for(int y = 1; y <= n; y ++ )
        {
            if(dang[x][y]) continue;
            for(int u = 0; u < 8; u ++ )
            {
                int a = x + dx[u], b = y + dy[u];
                if(a < 1 || a > n || b < 1 || b > n) continue;
                if(dang[a][b]) continue;
                if((a + b) & 1) add(id[x][y], id[a][b], 1);
                else add(id[a][b], id[x][y], 1);
            }
        }
    

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            if(dang[i][j]) continue;
            if((i + j) & 1) add(id[i][j], t, 1);
            else add(s, id[i][j], 1);
        } 

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;
     

    cout << n * n - m - maxflow << endl;

    return 0;
}
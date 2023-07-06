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

const int N = 1e6 + 10, M = 110, INF = 0x3f3f3f3f;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int in[N], out[N];
int x[N], y[N];
char mp[M][M], frog[M][M];
int r, c, maxd;
int s, t;
int cnt, num;
int flow, maxflow;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

inline int get(int x, int y)
{
    return x * c + y;
}

inline bool vaild(int x, int y)
{
    return (x <= r && x > 0 && y <= c && y > 0);
}

inline int dist(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

inline int get2(int x, int y)
{
    return c * r + x * c + y;
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

int k;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    r = read(), c = read(), maxd = read();
    cnt = r * c + 1;
    t = N - 2;
    for(int i = 1; i <= r; i ++ ) scanf("%s", mp[i] + 1);

    for(int i = 1; i <= r; i ++ ) scanf("%s", frog[i] + 1);

    for(int i = 1; i <= r; i ++ )
        for(int j = 1; j <= c; j ++ )
        {
            in[get(i, j)] = get(i, j);
            out[get(i, j)] = get2(i, j);
            if(mp[i][j] != '0') add(get(i, j), out[get(i, j)], mp[i][j] - '0');
        }

    for(int i = 1; i <= r; i ++ )
        for(int j = 1; j <= c; j ++ )
            if(mp[i][j] != '0')
            {
                k ++;
                x[k] = i, y[k] = j;
            }

    for(int i = 1; i <= k; i ++ )
        for(int j = 1; j <= k; j ++ )
        {
            if(i == j) continue;
            if(dist(x[i], y[i], x[j], y[j]) <= maxd * maxd)
                add(out[get(x[i], y[i])], in[get(x[j], y[j])], INF);
        }

    for(int i = 1; i <= k; i ++ )
    {
        int x1 = x[i], y1 = y[i];
        if(x1 + maxd > r || x1 - maxd < 1 || y1 + maxd > c || y1 - maxd < 1) 
            add(out[get(x[i], y[i])], t, INF);
    }

    for(int i = 1; i <= r; i ++ )
        for(int j = 1; j <= c; j ++ )
            if(frog[i][j] == 'L')
            {
                add(s, in[get(i, j)], 1);
                num ++;
            }
    
    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    cout << num - maxflow << endl;
    
    return 0;
}

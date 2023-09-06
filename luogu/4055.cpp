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
const int M = 110;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int h[N], e[N], ne[N], w[N], idx;
char mp[M][M];
int s, t;
bitset<N> odd;
int flow, maxflow;
int maxtot;
int n, m;

inline int id(int x, int y)
{
    return (x - 1) * m + y;
}

inline PII get(int x)
{
    return {(x - 1) / m + 1, (x - 1) % m + 1};
}

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
int now[N], d[N];
bitset<N> st;
inline bool bfs()
{
    while(q.size()) q.pop();
    for(int i = 1; i <= n * m + 2; i ++ ) d[i] = INF, st[i] = false;
    q.push(s);
    d[s] = 0;
    st[s] = true;
    now[s] = h[s];

    while(q.size())
    {
        int u = q.front();
        q.pop();
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            now[v] = h[v];
            if(w[i] && d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return true;
            }
        }
    }
    return false;
}

inline int dinic(int u, int flow)
{
    if(u == t) return flow;
    int k, rest = flow;
    for(int i = now[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(w[i] && d[v] == d[u] + 1)
        {
            k = dinic(v, min(w[i], rest));
            if(!k) d[v] = INF;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

bitset<N> vis, ans;
int bel[N];
inline void dfs(int u, int lim)
{
    if(vis[u]) return;
    vis[u] = true;
    if(bel[u] == lim)
        ans[u] = true;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(w[i] == lim) dfs(v, lim);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    s = n * m + 1, t = n * m + 2;
    for(int i = 1; i <= n; i ++ ) scanf("%s", mp[i] + 1);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            if((i + j) & 1)
                odd[id(i, j)] = true;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j] == '#') continue;
            maxtot ++;
            int a = id(i, j);
            if(odd[a]) 
            {
                add(s, a, 1);
                bel[a] = 1;
            }
            else add(a, t, 1);
            for(int k = 0; k < 4; k ++ )
            {
                int x = i + dx[k], y = j + dy[k];
                if(x < 1 || x > n || y < 1 || y > n || mp[x][y] == '#') continue;
                int b = id(x, y);
                if(odd[a]) add(a, b, 1);
            }
        }

    while(bfs())    
        while(flow = dinic(s, INF))
            maxflow += flow;

    if(maxtot == maxflow * 2)
    {
        puts("LOSE");
        return 0;
    }

    dfs(s, 1);
    vis.reset();
    dfs(t, 0);

    puts("WIN");

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            if(ans[id(i, j)])
                printf("%d %d\n", i, j);

    return 0;
}

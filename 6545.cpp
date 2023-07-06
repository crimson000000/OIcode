#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, long long> PII;

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

const int N = 5e6 + 10, M = 410;

int h[N], e[N], ne[N], idx;
ll w[N], dist[N];
bool st[N], vis[N];
int n, m;
int a[M][M];
ll dnval[M][M], rgval[M][M];
bool dntag[M][M], rgtag[M][M];

inline int getid(int x, int y)
{
    return (x - 1) * (m + 1) + y;
}

inline int gety(int id)
{
    return (id - 1) % (m + 1) + 1;
}

inline int getx(int id)
{
    return (id - 1) / (m + 1) + 1;
}

inline void init()
{
    memset(h, -1, sizeof h);
    memset(st, 0, sizeof st);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(w, 0, sizeof w);
}

inline void add(int a, int b, ll c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    while(heap.size()) heap.pop();
    heap.push({0, s});
    dist[s] = 0;
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        
        int ver = t.second;
        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[ver] + w[i])
            {
                dist[v] = dist[ver] + w[i];
                heap.push({dist[v], v});
            }
        }
    }
}

void dfs(int u)
{
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(dist[u] == dist[v] + w[i])
        {
            int ux = getx(u), uy = gety(u), vx = getx(v), vy = gety(v);
            if(ux != vx) dntag[min(ux, vx)][uy] = true;
            else rgtag[ux][min(uy, vy)] = true;
            if(!vis[v]) dfs(v);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init();

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            a[i][j] = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m + 1; j ++ )
        {
            dnval[i][j] = read();
            int idu = getid(i, j), idv = getid(i + 1, j);
            add(idu, idv, dnval[i][j]);
            add(idv, idu, dnval[i][j]);
        }

    for(int i = 1; i <= n + 1; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            rgval[i][j] = read();
            int idu = getid(i, j), idv = getid(i, j + 1);
            add(idu, idv, rgval[i][j]);
            add(idv, idu, rgval[i][j]);
        }

    dijkstra(getid(1, 1));

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            if(!vis[getid(i, j)] && a[i][j] == 1)
                dfs(getid(i, j));

    idx = 0;
    init();
    for(int i = 1; i <= n + 1; i ++ )
        for(int j = 1; j <= m + 1; j ++ )
        {
            int bg = (getid(i, j) - 1) * 4;
            int _0 = bg + 1, _1 = bg + 2, _2 = bg + 3, _3 = bg + 4;
            if(!dntag[i - 1][j] && a[i - 1][j - 1] == 0 && a[i - 1][j] == 0)
                add(_0, _1, 0);
            if(!rgtag[i][j] && a[i - 1][j] == 0 && a[i][j] == 0)
                add(_1, _2, 0);
            if(!dntag[i][j] && a[i][j] == 0 && a[i][j - 1] == 0)
                add(_2, _3, 0);
            if(!rgtag[i][j - 1] && a[i][j - 1] == 0 && a[i - 1][j - 1] == 0)
                add(_3, _0, 0);
            if(i > 1)
            {
                int ubg = (getid(i - 1, j) - 1) * 4;
                int u2 = ubg + 3, u3 = ubg + 4;
                add(u2, _1, dnval[i - 1][j]);
                add(_0, u3, dnval[i - 1][j]);
            }
            if(j > 1)
            {
                int lbg = (getid(i, j - 1) - 1) * 4;
                int l1 = lbg + 2, l2 = lbg + 3;
                add(l1, _0, rgval[i][j - 1]);
                add(_3, l2, rgval[i][j - 1]);
            }
        }
    
    dijkstra(2);

    
    cout << dist[4] << endl;

    return 0;
}
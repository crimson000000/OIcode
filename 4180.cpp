#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 1e5 + 10, M = 3e5 + 10, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
struct Edge
{
    int a, b, w;
    bool used;
    bool operator < (const Edge& W) const
    {
        return w < W.w;
    }
}edge[M];
int n, m;
int p[N];
int f[N][17], d1[N][17], d2[N][17], dep[N];
int q[N];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

ll kruskal()
{
    ll res = 0;
    for(int i = 0; i < m; i ++ )
    {
        int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
        if(a != b)
        {
            p[a] = b;
            res += w;
            edge[i].used = true;
            add(edge[i].a, edge[i].b, w), add(edge[i].b, edge[i].a, w);
        }
    }
    return res;
}

void bfs()
{
    memset(dep, 0x3f, sizeof dep);
    dep[0] = 0;
    dep[1] = 1;
    int hh = 0, tt = 0;
    q[0] = 1;
    while(hh <= tt)
    {
        int t = q[hh ++ ];
        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dep[j] > dep[t] + 1)
            {
                dep[j] = dep[t] + 1;
                q[++ tt] = j;
                f[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = -INF;
                for(int k = 1; k <= 16; k ++ )
                {
                    int anc = f[j][k - 1];
                    f[j][k] = f[anc][k - 1];
                    int distance[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    d1[j][k] = -INF, d2[j][k] = -INF;
                    for(int u = 0; u < 4; u ++ )
                    {
                        int dw = distance[u];
                        if(dw > d1[j][k]) d2[j][k] = d1[j][k], d1[j][k] = dw;
                        else if(dw != d1[j][k] && dw > d2[j][k]) d2[j][k] = dw; 
                    }
                }
            }
        }
    }
}

int lca(int a, int b, int w)
{
    if(dep[a] < dep[b]) swap(a, b);
    int distance[N * 2];
    int cnt = 0;
    for(int i = 16; i >= 0; i -- )
        if(dep[f[a][i]] >= dep[b])
        {
            distance[cnt ++ ] = d1[a][i];
            distance[cnt ++ ] = d2[a][i];
            a = f[a][i];
        }
    if(a != b)
    {
        for(int i = 16; i >= 0; i -- )
            if(f[a][i] != f[b][i])
            {
                distance[cnt ++ ] = d1[a][i];
                distance[cnt ++ ] = d2[a][i];
                distance[cnt ++ ] = d1[b][i];
                distance[cnt ++ ] = d2[b][i];
                a = f[a][i], b = f[b][i];
            }
            distance[cnt ++ ] = d1[a][0];
            distance[cnt ++ ] = d1[b][0];
    }
    int wd1 = -INF, wd2 = -INF;
    for(int i = 0; i < cnt; i ++ )
    {
        int d = distance[i];
        if(d > wd1) wd2 = wd1, wd1 = d;
        else if(d != wd1 && d > wd2) wd2 = d;
    }
    if(w > wd1) return w - wd1;
    if(w > wd2) return w - wd2;
    return INF;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    memset(h, -1, sizeof h);

    for(int i = 1; i <= n; i ++ ) p[i] = i;
   
    for(int i = 0; i < m; i ++ )
    {
        int a = read(), b = read(), c = read();
        edge[i] = {a, b, c};
    }

    sort(edge, edge + m);

    ll sum = kruskal();
    
    bfs();

    ll res = 1e18;
    for(int i = 0; i < m; i ++ )
    {
        if(!edge[i].used)
        {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            res = min(res, sum + lca(a, b, w));
        }
    }    

    cout << res << endl;

    return 0;
}

#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;

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

const int N = 3e6 + 10, M = 1010;
int h[N], e[N], ne[N];
int a[M][M], b[M][M], c[M][M];
int id[M][M];
ll w[N], idx;
int n, m;

int s, t;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

ll dist[N];
bitset<N> st;
priority_queue<PII, vector<PII>, greater<PII>> q;
inline void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    q.push({0, s});
    while(q.size())
    {
        auto t = q.top();
        q.pop();
        
        int u = t.second;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + w[i])
            {
                dist[v] = dist[u] + w[i];
                q.push({dist[v], v});
            }
        }
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
    s = 2 * n * m + 1, t = 2 * n * m + 2;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j < m; j ++ )
            a[i][j] = read();
    
    for(int i = 1; i < n; i ++ )
        for(int j = 1; j <= m; j ++ )
            b[i][j] = read();

    for(int i = 1; i < n; i ++ )
        for(int j = 1; j < m; j ++ )
            c[i][j] = read();
    
    n --, m --;
    if(!n)
    {
        int res = 0x3f3f3f3f;
        for(int i = 1; i <= m; i ++ ) 
            res = min(res, a[1][i]);
        cout << res << endl;
        return 0;
    }

    if(!m)
    {
        int res = 0x3f3f3f3f;
        for(int i = 1; i <= n; i ++ )
            res = min(res, b[i][1]);
        cout << res << endl;
        return 0;
    }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            id[i][j] = (i - 1) * m * 2 + j;

    s = n * m * 2 + 1, t = n * m * 2 + 2;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            add(id[i][j], id[i][j] + m, c[i][j]);
            add(id[i][j] + m, id[i][j], c[i][j]);
        }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j < m; j ++ )
        {
            add(id[i][j], id[i][j + 1] + m, b[i][j + 1]);
            add(id[i][j + 1] + m, id[i][j], b[i][j + 1]);
        }

    for(int i = 1; i < n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            add(id[i][j] + m, id[i + 1][j], a[i + 1][j]);
            add(id[i + 1][j], id[i][j] + m, a[i + 1][j]);
        }

    for(int i = 1; i <= m; i ++ )
    {
        add(id[1][i], t, a[1][i]);
        add(s, id[n][i] + m, a[n + 1][i]);
    }

    for(int i = 1; i <= n; i ++ )
    {
        add(id[i][m], t, b[i][m + 1]);
        add(s, id[i][1] + m, b[i][1]);
    }

    dijkstra(s);

    cout << dist[t] << endl;

    return 0;
}

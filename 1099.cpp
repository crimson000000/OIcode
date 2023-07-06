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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int n, s;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int d[N], maxd, maxv;
int st, ed;
int pre[N];
vector<int> dia;
queue<int> q;
bitset<N> vis;

namespace diameter
{ 
    void bfs1(int a)
    {
        maxd = 0, maxv = 0;
        vis.reset();
        q.push(a);
        vis[a] = true;
        d[a] = 0;
        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = h[u]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(vis[v]) continue;
                vis[v] = true;
                d[v] = d[u] + w[i];
                pre[v] = u;
                if(d[v] > maxd)
                {
                    maxd = d[v];
                    maxv = v;
                }
                q.push(v);
            }
        }
    }
    void main()
    {
        bfs1(1); st = maxv;
        bfs1(st); ed = maxv;

        int _u = ed;
        while(_u != st)
        {
            dia.push_back(_u);
            _u = pre[_u];
        }

        dia.push_back(st);
        // for(auto u : dia)
        // {
        //     printf("%d: %d\n", u, d[u]);
        // }
        return;
    }
}

bitset<N> core;
int far, ans = 0x3f3f3f3f;
int dist[N];

void bfs()
{
    for(int i = 1; i <= n; i ++ )
    {
        vis[i] = false;
        if(core[i])
        {
            q.push(i);
            dist[i] = 0;
            vis[i] = true;
        }
    }
    
    while(q.size())
    {
        int u = q.front();
        q.pop();

        far = max(far, dist[u]);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(vis[v]) continue;
            dist[v] = dist[u] + w[i];
            vis[v] = true;
            q.push(v);
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

    n = read(), s = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    diameter::main();

    for(int i = 0, j = 0; i < dia.size(); i ++ )
    {
        core[dia[i]] = true;
        while(j != (int)dia.size() - 1 && d[dia[i]] - d[dia[j + 1]] <= s) 
        {
            j ++;
            core[dia[j]] = true;
        }
        
        far = 0;
        for(int k = 1; k <= n; k ++ ) dist[k] = 0;
        bfs();
        // printf("%d %d %d\n", i, j, far);
        ans = min(ans, far);
        core[dia[i]] = false;
    }

    printf("%d\n", ans);

    return 0;
}
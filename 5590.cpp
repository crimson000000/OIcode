#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct edge
{
    int v, w;
    edge(int _v, int _w): v(_v), w(_w) {};
};
vector<edge> G[N];
int h[N], e[N], ne[N], idx;
int dist[N];
bitset<N> st;
queue<int> q;
int n, m;
int ansu[N], ansv[N], answ[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
} 

int cnt[N];
inline bool spaf(int s)
{
    memset(dist, 0x3f, sizeof dist);
    q.push(s);
    st[s] = true;
    dist[s] = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;
        for(auto e : G[u])
        {
            int v = e.v, w = e.w;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > n) return false;
                if(!st[v])
                {
                    st[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

bitset<N> vis, nto;
inline bool dfs(int u)
{
    if(u == n || nto[u]) return true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[i]) continue;
        vis[i] = true;
        if(dfs(v))
        {
            G[u].emplace_back(v, 9);
            G[v].emplace_back(u, -1);
            nto[u] = true;
        }
    }
    return nto[u];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int u = read(), v = read();
        add(u, v);
        ansu[i] = u, ansv[i] = v;
    }

    for(int i = 1; i <= n; i ++ ) G[0].emplace_back(i, 0);
    
    if(!dfs(1) || !spaf(0))
    {
        puts("-1");
        return 0;
    }

    printf("%d %d\n", n, m);
    for(int i = 1; i <= m; i ++ )
    {
        int now = dist[ansv[i]] - dist[ansu[i]];
        printf("%d %d ", ansu[i], ansv[i]);
        if(now >= 1 && now <= 9) printf("%d\n", now);
        else printf("1\n");
    }

    return 0;
}

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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
bool vis[N];
int n, k;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int siz[N], maxsize[N];
int rt;
void calc_size(int u, int fa, int sz)
{
    siz[u] = 1, maxsize[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        calc_size(j, u, sz);
        siz[u] += siz[j];
        maxsize[u] = max(maxsize[u], siz[j]);
    }
    maxsize[u] = max(maxsize[u], sz - siz[u]);
    if(maxsize[u] < maxsize[rt])
    {
        rt = u;
    }
}

ll dist[N];
int dep[N], cntt[N];
ll dd[N], tt;
void calc_dist(int u, int fa)
{
    dd[++ tt] = dist[u];
    cntt[tt] = dep[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = dist[u] + w[i];
        dep[j] = dep[u] + 1;
        calc_dist(j, u);
    }
}

int ans = INF;
int tf[N];
queue<int> tag;
void dfz(int u)
{
    vis[u] = true;
    tf[0] = 0;
    tag.push(0);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        dep[j] = 1;
        dist[j] = w[i];
        calc_dist(j, u);
        for(int z = 1; z <= tt; z ++ )
        {
            int x = -1;
            if(k >= dd[z]) x = tf[k - dd[z]];
            if(x == -1) continue;
            ans = min(ans, x + cntt[z]);
        }
        for(int z = 1; z <= tt; z ++ )
        {
            if(dd[z] <= 1000000)
            {
                tf[dd[z]] = min(tf[dd[z]], cntt[z]);
                tag.push(dd[z]);
            }
        }
        tt = 0;
    }

    while(tag.size()) tf[tag.front()] = INF, tag.pop();
    
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        rt = 0;
        maxsize[rt] = INF;
        calc_size(j, u, siz[j]);
        calc_size(rt, -1, siz[j]);
        dfz(rt);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(tf, 0x3f, sizeof tf);

    n = read(), k = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read() + 1, b = read() + 1, c = read();
        add(a, b, c), add(b, a, c);
    }

    rt = 0;
    maxsize[rt] = INF;
    calc_size(1, -1, n);
    calc_size(rt, -1, n);

    dfz(rt);
    if(ans >= INF) ans = -1;
    cout << ans << endl;
    
    return 0;
}

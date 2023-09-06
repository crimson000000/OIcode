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
int h[N], e[N], ne[N], idx;
bool vis[N];
int n, k;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int maxsize[N], siz[N];
int rt;
void calc_size(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsize[u] = 0;
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

int dist[N];
int dd[N], tt;
void calc_dist(int u, int fa)
{
    dd[++ tt] = dist[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = dist[u] + 1;
        calc_dist(j, u);
    }
}

ll tf[N];
ll ans;
queue<int> tag;
void dfz(int u)
{
    vis[u] = true;
    tf[0] = 1;
    tag.push(0);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        dist[j] = 1;
        calc_dist(j, u);
        for(int x = 1; x <= tt; x ++ )
            if(k - dd[x] >= 0) 
                ans += tf[k - dd[x]];
        for(int x = 1; x <= tt; x ++ )
        {
            tf[dd[x]] ++;
            tag.push(dd[x]);
        }
        tt = 0;
    }
    while(tag.size()) tf[tag.front()] = 0, tag.pop();
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

    n = read(), k = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    rt = 0;
    maxsize[rt] = INF;
    calc_size(1, -1, n);
    calc_size(rt, -1, n);
    dfz(rt);

    cout << ans << endl;
    
    return 0;
}

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
int n, m, k;
int h[N], e[N], w[N], ne[N], idx;
int dist[N];
int siz[N], maxsiz[N];
int q[N];
bool tf[N * 10];
bool vis[N], res[N];
int rt;

inline void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        calc_siz(j, u, sz);
        siz[u] += siz[j];
        maxsiz[u] = max(maxsiz[u], siz[j]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt])
    {
        rt = u;
    }
}

int dd[N], tt;
void calc_dist(int u, int fa)
{
    dd[++ tt] = dist[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = dist[u] + w[i];
        calc_dist(j, u);
    }
}

queue<int> tag;
void dfz(int x, int fa)
{
    tf[0] = true;
    tag.push(0);
    vis[x] = true;
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        dist[j] = w[i];
        calc_dist(j, x);
        for(int k = 1; k <= tt; k ++ )
            for(int u = 1; u <= m; u ++ )
                if(q[u] >= dd[k]) res[u] |= tf[q[u] - dd[k]];
        for(int k = 1; k <= tt; k ++ )
            if(dd[k] < 10000000)
            {
                tf[dd[k]] = true;
                tag.push(dd[k]);
            }
        tt = 0;
    }
    while(!tag.empty()) tf[tag.front()] = false, tag.pop();
    for(int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(j, x, siz[j]);
        calc_siz(rt, -1, siz[j]);
        dfz(rt, x);
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    for(int i = 1; i <= m; i ++ )
        q[i] = read();

    rt = 0;
    maxsiz[rt] = INF;
    siz[1] = n;
    calc_siz(1, -1, n);
    calc_siz(rt, -1, n);
    dfz(rt, -1);
    for(int i = 1; i <= m; i ++ )
        if(res[i])
            puts("AYE");
        else puts("NAY");
    
    return 0;
}

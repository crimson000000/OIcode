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
int n;

inline void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
}

inline int mod(int x, int p)
{
    return x - (x / p) * p;
}

inline int max(int a, int b)
{
    if(a > b) return a;
    return b;
}

int maxsize[N], siz[N];
int rt;
inline void calc_size(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsize[u] = 0;
    for(register int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(!(j ^ fa) || vis[j]) continue;
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
inline void calc_dist(int u, int fa)
{
    dd[++ tt] = dist[u] % 3;
    for(register int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if(!(j ^ fa) || vis[j]) continue;
        dist[j] = mod(dist[u] + w[i], 3);
        calc_dist(j, u);
    }
}

int tf[10], ans;
inline void dfz(int x)
{
    vis[x] = true;
    tf[0] = 1;
    for(register int i = h[x]; ~i; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        dist[j] = mod(w[i], 3);
        calc_dist(j, x);
        for(register int i = 1; i <= tt; i ++ )
            ans += tf[mod(3 - dd[i], 3)];
        for(register int i = 1; i <= tt; i ++ ) 
            tf[dd[i]] ++;
        tt = 0;
    }
    tf[0] = tf[1] = tf[2] = 0;
    for(register int i = h[x]; ~i; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        rt = 0;
        maxsize[rt] = INF;
        calc_size(j, x, siz[j]);
        calc_size(rt, -1, siz[j]);
        dfz(j);
    }    
}

inline int gcd(int a, int b)
{
    if(!b) return a;
    return gcd(b, mod(a, b));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(register int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    rt = 0;
    maxsize[rt] = INF;
    calc_size(1, -1, n);
    calc_size(rt, -1, n);
    dfz(rt);

    int d = gcd((ans << 1) + n, (ll)n * n);
    int up = ((ans << 1) + n) / d, down = (ll)n * n / d;
    printf("%d/%d\n", up, down);
    
    return 0;
}

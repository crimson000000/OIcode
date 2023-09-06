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

const int N = 2e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
int n, m, s;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

struct seg
{
    int l, r;
    int maxn, id;
}t[N << 2];

inline void pushup(int p)
{
    t[p].maxn = min(t[p << 1].maxn, t[p << 1 | 1].maxn);
    if(t[p << 1].maxn == t[p].maxn) t[p].id = t[p << 1].id;
    if(t[p << 1 | 1].maxn == t[p].maxn) t[p].id = t[p << 1 | 1].id;
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].maxn = dist[l];
        t[p].id = l;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change(int p, int pos, int v)
{
    if(t[p].l == t[p].r)
    {
        t[p].maxn = v;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos, v);
    else change(p << 1 | 1, pos, v);
    pushup(p);
}

bitset<N> st;
inline void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    build(1, 1, n);
    int count = 0;
    while(count != n)
    {
        int u = t[1].id;
        
        if(st[u]) continue;
        st[u] = true;
        change(1, u, INF);
        count ++;
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + w[i])
            {
                dist[v] = dist[u] + w[i];
                change(1, v, dist[v]);
            }
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), s = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }

    dijkstra(s);

    for(int i = 1; i <= n; i ++ )
        printf("%d ", dist[i]);
    
    return 0;
}

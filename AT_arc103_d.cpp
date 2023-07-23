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
const ll INF = 0x3f3f3f3f3f3f3f3f;
unordered_map<ll, int> mp;
ll d[N];
int n;
int siz[N];

struct seg
{
    int l, r;
    ll maxn;
}t[N << 2];
int rt;

inline void pushup(int p)
{
    t[p].maxn = max(t[p << 1].maxn, t[p << 1 | 1].maxn);
}

inline void build(int p, int l ,int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) 
    {
        t[p].maxn = d[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change(int p, int pos, ll v)
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

inline void nosol()
{
    puts("-1");
    exit(0);
}

int h[N], e[N], ne[N], idx;
ll dist[N], ans[N];
int ansu[N], ansv[N], tt;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void dfs1(int u, int fa)
{
    // dist[u] = dist[fa] + 1;
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        // printf("%d %d\n", u, v);
        dist[v] = dist[u] + 1;
        dfs1(v, u);
        siz[u] += siz[v];
    }
}

inline void dfs2(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        ans[v] = ans[u] - 2 * siz[v] + n;
        dfs2(v, u);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    d[0] = INF;
    for(int i = 1; i <= n; i ++ )
    {
        d[i] = read();
        mp[d[i]] = i;
        if(d[i] < d[rt]) rt = i;
    }

    build(1, 1, n);

    for(int test = 1; test < n; test ++ )
    {
        ll maxn = t[1].maxn;
        int v = mp[maxn];
        change(1, v, 0);
        siz[v] ++;
        ll dfa = d[v] - n + 2 * siz[v];
        // printf("%lld %lld\n", maxn, dfa);
        if(!mp.count(dfa)) 
        {
            // puts("fcu");
            nosol();
        }

        int u = mp[dfa];
        siz[u] += siz[v];
        tt ++;
        ansu[tt] = u, ansv[tt] = v;
        add(u, v), add(v, u);
    }

    dfs1(rt, rt);
    for(int i = 1; i <= n; i ++ ) ans[rt] += dist[i];
    dfs2(rt, rt);

    // for(int i = 1; i <= n; i ++ ) cout << ans[i] << ' ';

    sort(ans + 1, ans + n + 1);
    sort(d + 1, d + n + 1);

    for(int i = 1; i <= n; i ++ )
        if(ans[i] != d[i])
            nosol();

    for(int i = 1; i <= tt; i ++ )
        printf("%d %d\n", ansu[i], ansv[i]);

    return 0;
}

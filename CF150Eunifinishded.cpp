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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int L, R;
int n;

struct edge
{
    int a, b, c;
}ed[N];

struct wtmcnm
{
    int u, dist, dep;
};

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

bool flag;

int siz[N], maxsiz[N], rt;
bitset<N> vis;
inline void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        calc_siz(v, u, sz);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt])
    {
        rt = u;
    }
}

PII mdist[N];
PII ndep[N];
wtmcnm dist[N];
int q[N];
int hh, tt;
int maxdep;
int cnt;
int st, endd;

void calc_dis(int u, int fa, int d, int dep)
{
    dist[++ cnt] = {u, d, dep};
    maxdep = max(maxdep, dep);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        calc_dis(v, u, d + w[i], dep + 1);
    }
}

void dfz(int u)
{
    vis[u] = true;
    mdist[0] = {0, u};
    int mmmdep = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;
        maxdep = -INF;
        cnt = 0;
        calc_dis(v, u, w[i], 1);
        mmmdep = max(mmmdep, maxdep);

        for(int i = 1; i <= tt; i ++ ) 
            ndep[dist[i].dep] = max(ndep[dist[i].dep], make_pair(dist[i].dist, dist[i].u));
        
        hh = 0, tt = -1;
        for(int i = R; i >= L; i -- )
        {
            while(hh <= tt && mdist[q[tt]] <= mdist[i]) tt --;
            q[++ tt] = i;
        }

        if(mdist[q[hh]].first >= 0)
        {
            flag = true;
            st = u, endd = mdist[q[hh]].second;
        }
        for(int dep = 1; dep <= maxdep; dep ++ )
        {
            while(hh <= tt && q[hh] > R - dep) hh ++;
            if(L - dep >= 0) 
            {
                while(hh <= tt && mdist[q[tt]] <= mdist[L - dep]) tt --;
                q[++ tt] = L - dep;
            }
            
            if(mdist[q[hh]].first + ndep[dep].first >= 0) 
            {
                flag = true;
                st = mdist[q[hh]].second;
                endd = ndep[dep].second;
            }
        }

        for(int i = 0; i <= maxdep; i ++ ) mdist[i] = max(mdist[i], ndep[i]);
        for(int i = 0; i <= maxdep; i ++ ) ndep[i].first = -INF;
    }

    for(int i = 0; i <= mmmdep; i ++ ) mdist[i].first = -INF;

    if(flag) return;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;

        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(v, u, siz[v]);
        calc_siz(rt, rt, siz[v]);
        dfz(rt);
    }
}

inline bool check(int mid)
{
    flag = false;
    idx = 0;
    memset(h, -1, sizeof h);
    vis.reset();
    for(int i = 1; i < n; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c >= mid ? 1 : -1;
        add(a, b, c), add(b, a, c);
    }

    rt = 0;
    maxsiz[rt] = INF;
    calc_siz(1, 0, n);
    calc_siz(rt, 0, n);
    dfz(rt);
    
    return flag;
}

signed main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), L = read(), R = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        ed[i] = {a, b, c};
    }

    int l = 0, r = 1e9;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << l << endl;

    cout << st << ' ' << endd << endl;

    return 0;
}
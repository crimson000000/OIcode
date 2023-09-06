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
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}
#define int ll

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, M;
int h[N], e[N], ne[N], w[N], idx;
ll inv10[N], mi10[N];

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

inline ll INV(ll a)
{
    ll x, k;
    exgcd(a, M, x, k);
    return (x % M + M) % M;
}

int siz[N], maxsiz[N], rt;
bitset<N> vis;
void calc_siz(int u, int fa, int sz)
{
    maxsiz[u] = 0;
    siz[u] = 1;
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

ll ans;
map<ll, ll> cnt;
pair<ll, ll> dist[N];
int tt;

void dfs(int u, int fa, ll d1, ll d2, int dep)
{
    if(dep >= 0) cnt[d1] ++, dist[++ tt] = {d2, dep};
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[v]) continue;
        ll dd1 = (d1 + w[i] * mi10[dep + 1]) % M;
        ll dd2 = (d2 * 10 + w[i]) % M;
        dfs(v, u, dd1, dd2, dep + 1);
    }
}

inline int calc(int u, int w = 0)
{
    cnt.clear();
    tt = 0;
    ll res = 0;
    if(!w) dfs(u, 0, 0, 0, -1);
    else dfs(u, 0, w % M, w % M, 0);
    for(int i = 1; i <= tt; i ++ )
    {
        ll tp = ((-dist[i].first * inv10[dist[i].second + 1]) % M + M) % M;
        if(cnt.find(tp) != cnt.end()) res += cnt[tp];
        if(!w && !dist[i].first) res ++;
    }
    if(!w) res += cnt[0];
    return res;
}

inline void dfz(int u)
{
    vis[u] = true;
    ans += calc(u, 0);

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[v]) continue;
        ans -= calc(v, w[i]);
        int sum = siz[v];
        rt = 0;
        maxsiz[rt] = INF;
        calc_siz(v, u, sum);
        calc_siz(rt, rt, sum);
        dfz(rt);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), M = read();

    int _ = INV(10);
    inv10[0] = 1, mi10[0] = 1;
    for(int i = 1; i <= N - 5; i ++ ) 
    {
        mi10[i] = (ll)mi10[i - 1] * 10 % M;
        inv10[i] = inv10[i - 1] * _ % M;
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a + 1, b + 1, c), add(b + 1, a + 1, c);
    }

    rt = 0;
    maxsiz[rt] = INF;
    calc_siz(1, 0, n);
    calc_siz(rt, 0, n);
    dfz(rt);

    printf("%lld\n", ans);

    return 0;
}
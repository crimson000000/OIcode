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
int h[N], e[N], ne[N], c[N], idx;
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int siz[N];
int maxsize[N], rt;
bool vis[N];
void calc_size(int u, int fa, int sz)
{
    maxsize[u] = 0;
    siz[u] = 1;
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

ll ans[N], sum;
int cnt[N], v[N];
int nowrt;

void get_dist(int u, int fa, int now)
{
    siz[u] = 1;
    if(!v[c[u]])
    {
        sum -= cnt[c[u]];
        now ++;
    }
    v[c[u]] ++;
    ans[u] += sum + now * siz[nowrt];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        get_dist(j, u, now);
        siz[u] += siz[j];
    }
    v[c[u]] --;
    if(!v[c[u]])
    {
        sum += cnt[c[u]];
    }
}

void getcnt(int u, int fa)
{
    if(!v[c[u]])
    {
        cnt[c[u]] += siz[u];
        sum += siz[u];
    }
    v[c[u]] ++; 
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        getcnt(j, u);
    }
    v[c[u]] --;
}

void clear(int u, int fa, int now)
{
    if(!v[c[u]]) now ++;
    v[c[u]] ++;
    ans[u] -= now;
    ans[nowrt] += now;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        clear(j, u, now);
    }
    v[c[u]] --;
    cnt[c[u]] = 0;
}

void clear2(int u, int fa)
{
    cnt[c[u]] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa || vis[j]) continue;
        clear2(j, u);
    }
}

int son[N];
void dfz(int u)
{
    vis[u] = true;
    int tot = 0;
    nowrt = u;
    ans[u] ++;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        son[++ tot] = j;
    }
    siz[u] = sum = cnt[c[u]] = 1;
    v[c[u]] ++;
    for(int i = 1; i <= tot; i ++ )
    {
        int d = son[i];
        get_dist(d, u, 0);
        getcnt(d, u);
        siz[u] += siz[d];
        sum += siz[d];
        cnt[c[u]] += siz[d];
    }
    clear2(u, 0);
    sum = siz[u] = cnt[c[u]] = 1;
    for(int i = tot; i; i -- )
    {
        int d = son[i];
        get_dist(d, u, 0);
        getcnt(d, u);
        siz[u] += siz[d];
        sum += siz[d];
        cnt[c[u]] += siz[d];
    }
    v[c[u]] --;
    clear(u, 0, 0);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(vis[j]) continue;
        rt = 0;
        maxsize[rt] = INF;
        calc_size(j, -1, siz[j]);
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

    n = read();
    for(int i = 1; i <= n; i ++ ) c[i] = read();
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

    for(int i = 1; i <= n; i ++ ) printf("%lld\n", ans[i]);

    return 0;
}

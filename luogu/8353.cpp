#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ui = unsigned int;
using PII = pair<ll, ll>;

namespace INPUT_SPACE
{
    const int S = (1 << 20) + 5;
    char B[S], *H, *T;
    inline int gc()
    {
        if (H == T)
            T = (H = B) + fread(B, 1, S, stdin);
        return (H == T) ? EOF : *H++;
    }

    inline unsigned int read()
    {
        unsigned int x, ch;
        while ((ch = gc()) < '0' || ch > '9')
            ;
        x = ch ^ '0';
        while ((ch = gc()) >= '0' && ch <= '9')
            x = x * 10 + (ch ^ '0');
        return x;
    }
}

const int N = 7e6 + 10, M = 6000 + 10;
using INPUT_SPACE::read;
int idd, n, m, Bl;
ui A, B, C;
ui lastans;
ui a[N];
int fa[N];
bitset<N> vis, tag;
unordered_map<int, int> id, nxt[M];
int pos[M];
int tot;
ui sum[M], add[M], siz[M];
int FA[M], dep[M];
mt19937 rnd(time(0));

int getid(int x)
{
    return lower_bound(pos + 1, pos + tot + 1, x) - pos;
}

int depth(int x)
{
    int d = 0;
    while(!vis[x]) d ++, x = fa[x];
    return d + dep[getid(x)]; 
}

int find(int u)
{
    while(!vis[fa[u]]) u = fa[u];
    return nxt[getid(fa[u])][u];
}

void update(int u, ui w)
{
    if(!u) return;
    for(; !tag[u]; u = fa[u]) a[u] += w;
    if(!vis[u])
    {
        int x = find(u), y = FA[x];
        for(int v = pos[x]; v != pos[y]; v = fa[v]) a[v] += add[x];
        for(int v = u; v != pos[y]; v = fa[v]) a[v] += w, sum[x] += w;
        add[x] = 0;
        u = pos[y];
    }
    for(u = getid(u); u; u = FA[u]) 
        sum[u] += w * (dep[u] - dep[FA[u]]), add[u] += w;
}

ui query(int u)
{
    if(!u) return 0;
    ui res = 0;
    for(; !tag[u]; u = fa[u]) res += a[u];
    if(!vis[u])
    {
        int x = find(u), y = FA[x];
        for(int v = pos[x]; v != pos[y]; v = fa[v]) a[v] += add[x];
        for(int v = u; v != pos[y]; v = fa[v]) res += a[v];
        add[x] = 0;
        u = pos[y];
    }
    for(u = getid(u); u; u = FA[u]) 
        res += sum[u];
    return res;
}

int LCA(int x, int y)
{
    while(x != y) 
    {
        if(dep[x] < dep[y]) y = FA[y];
        else x = FA[x];
    }
    return x;
}

int lca(int u, int v)
{
    int x = u, y = v, depu = depth(u), depv = depth(v);
    while(!tag[x]) x = fa[x];
    while(!tag[y]) y = fa[y];
    if(x == y)
    {
        while(u != v)
        {
            if(depu < depv) v = fa[v], depv --;
            else u = fa[u], depu --;
        }
        return u;
    }

    u = x, v = y;
    if(vis[x]) x = getid(x);
    else x = find(x);
    if(vis[y]) y = getid(y);
    else y = find(y);

    if(x == y) 
    {
        if(depth(u) < depth(v)) return u;
        return v;
    }

    int z = LCA(x, y);
    if(z == x) return u;
    if(z == y) return v;
    return pos[z];
}

void change(int x, int y, ui w)
{
    if(x == y) 
    {
        update(x, w);
        update(fa[x], -w);
        return;
    }
    int lc = lca(x, y);
    if(x == lc)
    {
        update(y, w);
        update(fa[lc], -w);
        return;
    }
    if(y == lc)
    {
        update(x, w);
        update(fa[lc], -w);
        return;
    }
    update(x, w), update(y, w);
    update(lc, -w), update(fa[lc], -w);
}

ui query(int x, int y)
{
    if(x == y) return query(x) - query(fa[x]);
    int lc = lca(x, y);
    if(x == lc) return query(y) - query(fa[lc]);
    if(y == lc) return query(x) - query(fa[lc]);
    return query(x) + query(y) - query(lc) - query(fa[lc]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    idd = read(), n = read(), m = read();
    A = read(), B = read(), C = read(), a[0] = read();

    for(int i = 1; i <= n; i ++ )
        a[i] = (A * a[i - 1] * a[i - 1] + B * a[i - 1] + C);

    for(int i = 2; i <= n; i ++ ) fa[i] = read();

    Bl = sqrt(n);
    for(int i = 1; i <= Bl; i ++ ) 
    {
        int x = rnd() % n + 1;
        while(vis[x]) x = rnd() % n + 1;
        vis[x] = true;
        pos[++ tot] = x;
    }

    if(!vis[1]) 
    {
        vis[1] = true;
        pos[++ tot] = 1;
    }

    sort(pos + 1, pos + tot + 1);

    tag[1] = true; 
    for(int i = 1; i <= tot; i ++ )
    {
        int u = pos[i];
        for(; !tag[u]; u = fa[u]) tag[u] = true;
        if(!vis[u]) pos[++ tot] = u, vis[u] = true;
    }

    sort(pos + 1, pos + tot + 1);
    sum[1] = a[1], dep[1] = 1;
    for(int i = 2; i <= tot; i ++ )
    {
        sum[i] = a[pos[i]];
        dep[i] = 1;
        int p = fa[pos[i]], lst = pos[i];
        for(; !vis[p]; lst = p, p = fa[p])
        {
            sum[i] += a[p];
            dep[i] ++;
        }
        FA[i] = getid(p);
        dep[i] += dep[FA[i]];
        nxt[FA[i]][lst] = i;
    }

    while(m -- ) 
    {
        ui P = lastans & ((1 << 20) - 1);
        int op = read(), x = read() ^ P, y = read() ^ P;
        if(!op)
        {
            ui v = read() ^ P;
            change(x, y, v);
        }
        else
        {
            printf("%u\n", lastans = query(x, y));
        }
        // cerr << "yeah" << endl;
    }

    return 0;
}

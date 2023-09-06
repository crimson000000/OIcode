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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 40010;
int h[N], e[N], ne[N], idx;
ll v[N];
int pos[N][64];
ll d[N][64];
int n, q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], dep[N], son[N], siz[N];
void dfs1(int u, int f)
{
    fa[u] = f, siz[u] = 1, dep[u] = dep[f] + 1;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            son[u] = j;
            maxsize = siz[j];
        } 
    }
}

int top[N];
void dfs2(int u, int t)
{
    top[u] = t;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

int LCA(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

void insert(int p, int pos[], ll d[])
{
    ll x = v[p];
    if(x == 0) return;
    for(int i = 60; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                d[i] = x, pos[i] = p;
                break;
            }
            if(dep[p] > dep[pos[i]]) swap(p, pos[i]), swap(x, d[i]);
            x ^= d[i];
        }
    }
}

void dfs(int u)
{
    for(int i = 0; i <= 60; i ++ )
        pos[u][i] = pos[fa[u]][i], d[u][i] = d[fa[u]][i];
    insert(u, pos[u], d[u]);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u]) continue;
        dfs(j);
    }
}

ll base[100];
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), q = read();
    for(int i = 1; i <= n; i ++ ) v[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
   
    dfs2(1, 1);
    dfs(1);

    while(q -- )
    {
        int x = read(), y = read();
        int anc = LCA(x, y);
        for(int i = 60; i >= 0; i -- )
            if(dep[pos[x][i]] >= dep[anc]) 
                base[i] = d[x][i];
            else base[i] = 0;
        for(int i = 60; i >= 0; i -- )
            if(dep[pos[y][i]] >= dep[anc])
            {
                ll a = d[y][i];
                if(a == 0) continue;
                for(int j = 60; j >= 0; j -- )
                {
                    if(a >> j & 1)
                    {
                        if(!base[j])
                        {
                            base[j] = a;
                            break;
                        }
                        a ^= base[j];
                    }
                }
            }
        ll ans = 0;
        for(int i = 60; i >= 0; i -- )
            ans = max(ans, ans ^ base[i]);
        printf("%lld\n", ans);
    }
    
    return 0;
}

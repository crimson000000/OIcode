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

const int N = 1e6 + 10, mod = 998244353;
vector<int> g[N], og[N];
int n, m, k;

namespace uni
{
    int p[N], siz[N], cnt[N];
    inline void init()
    {
        for(int i = 1; i <= n; i ++ ) 
        {
            p[i] = i;
            siz[i] = 1;
            cnt[1] ++;
        }
    }

    inline int find(int x)
    {
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    inline int merge(int x, int y)
    {
        x = find(x), y = find(y);
        // if(x == y) return 0;
        cnt[siz[x]] --;
        cnt[siz[y]] --;
        p[x] = y;
        siz[y] += siz[x];
        cnt[siz[y]] ++;
        return 1;
    }
}

int dfn[N], low[N], tim;
int stk[N], tt;
int num;

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u;
    for(auto v : og[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] == dfn[u])
            {
                int y;
                num ++;
                // printf("the square point is %d\n", num);
                // printf("it has ");
                do {
                    y = stk[tt -- ];
                    // printf("%d ", y);
                    g[num].emplace_back(y);
                    g[y].emplace_back(num);
                } while(y != v);
                // printf("%d\n", u);
                g[num].emplace_back(u);
                g[u].emplace_back(num);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int siz[N], minsiz, rt;
void find_root(int u, int f)
{
    siz[u] = (u <= n);
    int maxsiz = -1;
    for(auto v : g[u])
    {
        if(v == f) continue;
        find_root(v, u);
        siz[u] += siz[v];
        maxsiz = max(maxsiz, siz[v]);
    }
    maxsiz = max(maxsiz, n - siz[u]);
    if(maxsiz < minsiz)
    {
        minsiz = maxsiz;
        rt = u;
    }
}

int fa[N];
vector<int> buc[N];
void dfs(int u, int f)
{
    fa[u] = f;
    siz[u] = (u <= n);
    for(auto v : g[u])
    {
        if(v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
    if(u > n) buc[siz[u]].emplace_back(u);
}

ll ans1[N], ans2[N];
int rec[N];
bitset<N> vis;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    num = n;

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        og[a].emplace_back(b);
        og[b].emplace_back(a);
    }

    uni::init();
    tarjan(1);

    minsiz = 0x3f3f3f3f;
    find_root(1, 0);
    if(rt > n) rt = g[rt][0];
    dfs(rt, 0);

    for(int i = 1; i < n; i ++ )
    {
        for(auto u : buc[i])
            if(g[u].size() > 2)
                for(int j = 1; j < (int)g[u].size(); j ++ )
                    uni::merge(g[u][j - 1], g[u][j]);
        
        ans1[i] = (i * uni::cnt[i] == n);
        
        vector<int> vec;
        vec.clear();

        for(auto u : buc[i])
        {
            if(g[u].size() == 2)
            {
                if(uni::siz[uni::find(fa[u])] == 1)
                {
                    vis[u] = vis[fa[u]] = true;
                    uni::merge(fa[u], g[u][g[u][0] == fa[u]]);
                    vec.emplace_back(fa[u]);
                    rec[fa[u]] = 1;
                }
                else if(vis[fa[u]])
                    rec[fa[u]] ++;
            }
        }
        
        if(i * uni::cnt[i] + (i + 1) * uni::cnt[i + 1] == n)
        {
            ans2[i] = 1;
            for(auto u : vec) ans2[i] = ans2[i] * (rec[u] + (i == 1)) % mod;
        }

        for(auto u : buc[i])
        {
            if(g[u].size() == 2 && !vis[u])
            {
                for(int j = 1; j < (int)g[u].size(); j ++ )
                    uni::merge(g[u][j - 1], g[u][j]);
            }
        }

        // printf("now i is %d\n", i);
        // for(int j = 1; j <= n; j ++ )
        // {
        //     printf("fa: %d, siz: %d\n", uni::find(j), uni::siz[uni::find(j)]);
        // }

        // printf("ans1 is: %lld\nans2 is: %lld\n", ans1[i], ans2[i]);
    }

    if(!k)
    {
        ll ans = 0;
        for(int i = 1; i < n; i ++ ) ans = (ans + ans1[i]) % mod;
        printf("%lld\n", ans);
    }
    else
    {
        ll ans = mod - 1;
        for(int i = 1; i < n; i ++ ) ans = (ans + ans2[i]) % mod;
        for(int i = 2; i < n; i ++ ) ans = (ans - ans1[i] + mod) % mod;
        printf("%lld\n", ans); 
    }

    return 0;
}
#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e6 + 10;
int tr[N][26], link[N], len[N];
vector<int> G[N];
int idx, lst;
int n, m;
char s[N];

inline void init()
{
    link[0] = -1;
}

int ver[N];
inline void extend(char cc)
{
    int p = lst, cur = ++ idx, c = cc - 'a';
    len[cur] = len[p] + 1;
    while(p != -1 && !tr[p][c])
    {
        tr[p][c] = cur;
        p = link[p];
    }
    if(p == -1) link[cur] = 0;
    else
    {
        int q = tr[p][c];
        if(len[q] == len[p] + 1) link[cur] = q;
        else
        {
            int copy = ++ idx;
            len[copy] = len[p] + 1;
            link[copy] = link[q];
            for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
            while(p != -1 && tr[p][c] == q)
            {
                tr[p][c] = copy;
                p = link[p];
            }
            link[cur] = link[q] = copy;
        }
    }
    lst = cur;
}

//------------------------ 树剖

int fa[N], dep[N], son[N], siz[N];
inline void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    int maxsiz = -1;
    for(auto v : G[u])
    {
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
    }
}

int top[N], dfn[N], tim;
inline void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(auto v : G[u])
    {
        if(v == son[u]) continue;
        dfs2(v, v);
    }
}

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

namespace VT
{
    int a, b;
    int S[N], tt;
    int col[N];
    int stk[N], top;
    vector<int> G[N];
    bitset<N> used;
    queue<int> cn;
    ll sum[N][2];
    ll ans;

    inline void clear()
    {
        while(cn.size())
        {
            int u = cn.front();
            cn.pop();
            used[u] = false;
            G[u].clear();
            col[u] = 0;
            sum[u][0] = sum[u][1] = 0;
        }
        tt = 0, top = 0;
        ans = 0;
    }

    inline void add(int u, int v)
    {
        G[u].push_back(v);
        G[v].push_back(u);
        // cout << u << ' ' << v << endl;
        if(!used[u]) used[u] = true, cn.push(u);
        if(!used[v]) used[v] = true, cn.push(v);
    }

    inline void insert(int u)
    {
        int lc = lca(stk[top], u);
        while(top > 1 && dep[lc] <= dep[stk[top - 1]])
        {
            add(stk[top], stk[top - 1]);
            top --;
        }
        if(lc != stk[top])
        {
            add(lc, stk[top]);
            stk[top] = lc;
        }
        stk[++ top] = u;
    }

    inline void dfs(int u, int fa)
    {
        ll tmp = sum[u][0];
        for(auto v : G[u])
        {
            if(v == fa) continue;
            // cout << u << ' ' << v << endl;
            dfs(v, u);
            sum[u][0] += sum[v][0];
            sum[u][1] += sum[v][1];
        }
        for(auto v : G[u])
        {
            if(v == fa) continue;
            ans += sum[v][0] * (sum[u][1] - sum[v][1]) * len[u];
        }
        ans += tmp * sum[u][1] * len[u];
    }

    inline void solve()
    {
        a = read(), b = read();
        for(int i = 1; i <= a; i ++ ) 
        {
            int x = read();
            col[ver[x]] |= 1;
            sum[ver[x]][0] ++;
            S[++ tt] = ver[x];
        }
        
        for(int i = 1; i <= b; i ++ ) 
        {
            int x = read();
            col[ver[x]] |= 2;
            sum[ver[x]][1] ++;
            S[++ tt] = ver[x];
        }

        sort(S + 1, S + tt + 1, [](int x, int y){
            return dfn[x] < dfn[y];
        });
        
        stk[top = 1] = 0;
        int cnt = unique(S + 1, S + tt + 1) - S - 1;
        // cout << cnt << endl;
        for(int i = 1; i <= cnt; i ++ ) insert(S[i]);

        while(top > 1)
        {
            add(stk[top], stk[top - 1]);
            top --;
        }

        dfs(0, 0);

        printf("%lld\n", ans);
        clear();
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    scanf("%s", s + 1);
    
    init();
    for(int i = n; i; i -- ) extend(s[i]);

    int p = 0;
    for(int i = n; i; i -- )
    {
        p = tr[p][s[i] - 'a'];
        ver[i] = p;
    }

    for(int i = 1; i <= idx; i ++ ) G[link[i]].push_back(i);

    dfs1(0, 0);
    dfs2(0, 0);

    // for(int i = 1; i <= idx; i ++ ) cout << fa[i] << ' ';
    // for(int i = 1; i <= n; i ++ ) cout << ver[i] << ' ';
    // cout << lca(7, 5) << endl;

    while(m -- )
    {
        VT::solve();
    }

    return 0;
}
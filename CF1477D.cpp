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

const int N = 1e6 + 10;
int p[N], q[N];
vector<int> G[N];
set<int> E[N];
set<int> unvis;
int deg[N];
int tot;
int n, m;

inline void aded(int a, int b)
{
    E[a].insert(b);
    E[b].insert(a);
    deg[a] ++, deg[b] ++;
}

inline void add(int a, int b)
{
    G[a].emplace_back(b);
    G[b].emplace_back(a);
}

queue<int> que;
inline void find_MST()
{
    for(int i = 1; i <= n; i ++ )
        if(unvis.count(i))
        {
            unvis.erase(i);
            que.emplace(i);
            
            while(que.size())
            {
                int u = que.front();
                que.pop();
                for(auto it = unvis.begin(); it != unvis.end();)
                {
                    int v = *it;
                    it ++;
                    if(E[u].count(v)) continue;
                    unvis.erase(v);
                    que.emplace(v);
                    add(u, v);
                }
            }
        }
}

int col[N];
vector<int> Tcol[N];
int rt[N], siz[N];
int col_cnt;

inline void init()
{
    tot = n;
    col_cnt = 0;
    unvis.clear();
    for(int i = 1; i <= n; i ++ )
    {
        unvis.insert(i);
        G[i].clear();
        deg[i] = 0;
        p[i] = q[i] = 0;
        Tcol[i].clear();
        rt[i] = 0;
        siz[i] = 0;
        col[i] = 0;
        E[i].clear();
    }
}

inline void dfs(int u, int fa)
{
    if(!col[u])
    {
        bool flag = false;
        for(auto v : G[u])
            if(!col[v])
                flag = true;
        
        if(flag)
        {
            col[u] = ++ col_cnt;
            rt[col[u]] = u;
            siz[col[u]] ++;
            for(auto v : G[u])
                if(!col[v])
                {
                    col[v] = col[u];
                    siz[col[u]] ++;
                }
        }
        else
        {
            for(auto v : G[u])
                if(col[v])
                {
                    if(rt[col[v]] == v)
                    {
                        siz[col[v]] ++;
                        col[u] = col[v];
                    }
                    else if(siz[col[v]] > 2)
                    {
                        col[u] = ++ col_cnt;
                        siz[col[u]] = 2;
                        rt[col[u]] = u;
                        siz[col[v]] --;
                        col[v] = col[u];
                    }
                    else 
                    {
                        rt[col[v]] = v;
                        col[u] = col[v];
                        ++ siz[col[u]];
                    }
                    break;
                }        
        }
    }

    for(auto v : G[u])
        if(v != fa)
            dfs(v, u);
}

inline void solve()
{
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        aded(a, b);
    }

    for(int i = 1; i <= n; i ++ )
        if(deg[i] == n - 1)
        {
            que.emplace(i);
            unvis.erase(i);
        }

    while(que.size())
    {
        int u = que.front();
        que.pop();
        p[u] = q[u] = tot -- ;
        for(auto v : G[u])
        {
            deg[v] --;
            if(unvis.count(v) && deg[v] == tot - 1)
            {
                que.emplace(v);
                unvis.erase(v);
            }
        }
    }

    find_MST();
    for(int i = 1; i <= n; i ++ ) 
        if(!p[i] && !col[i])
            dfs(i, 0);

    for(int i = 1; i <= n; i ++ )
        if(col[i])
            Tcol[col[i]].emplace_back(i);
    
    for(int i = 1, s = 1; i <= col_cnt; i ++, s ++ )
    {
        q[rt[i]] = s;
        for(auto u : Tcol[i])
            if(u != rt[i])
            {
                p[u] = s;
                q[u] = ++ s;
            }
        p[rt[i]] = s;
    }   

    for(int i = 1; i <= n; i ++ ) printf("%d ", p[i]);
    puts("");
    for(int i = 1; i <= n; i ++ ) printf("%d ", q[i]);
    puts("");
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read(), m = read();
        init();

        solve();
    }

    return 0;
}

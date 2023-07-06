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
int h[N], e[N], ne[N], idx;
int hs[N];
vector<int> q[N];
int n, m;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], siz[N], son[N], dep[N];
int maxdep[N], longson[N];
void dfs1(int u, int f)
{
    fa[u] = f, dep[u] = dep[f] + 1;
    siz[u] = 1;
    maxdep[u] = dep[u];
    int maxsiz = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxsiz)
        {
            maxsiz = siz[v];
            son[u] = v;
        }
        if(maxdep[v] > maxdep[u])
        {
            maxdep[u] = maxdep[v];
            longson[u] = v;
        }
    }
}

int top[N], dfn[N], anti[N], tim;
void dfs2(int u, int t)
{
    top[u] = t;
    dfn[u] = ++ tim;
    anti[tim] = u;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

namespace kth
{
    int maxdep[N], son[N];
    void dfs1(int u, int f)
    {
        maxdep[u] = dep[u];
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            dfs1(v, u);
            if(maxdep[v] > maxdep[u])
            {
                maxdep[u] = maxdep[v];
                son[u] = v;
            }
        }
    }

    int top[N], dfn[N], anti[N], tim;
    void dfs2(int u, int t)
    {
        top[u] = t;
        dfn[u] = ++ tim;
        anti[tim] = u;
        if(!son[u]) return;
        dfs2(son[u], t);
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(j == fa[u] || j == son[u]) continue;
            dfs2(j, j);
        }
    }

    inline int kthfa(int u, int k)
    {
        while(k)
        {
            if(dep[u] - dep[top[u]] < k)
            {
                k -= dep[u] - dep[top[u]] + 1;
                u = fa[top[u]];
            } 
            else return anti[dfn[u] - k];
        }
        return u;
    }
}

int c[N];

inline bool in_son(int u, int fa)
{
    return (dfn[u] >= dfn[fa] && dfn[u] <= dfn[fa] + siz[fa] - 1);
}

int din[N];
bitset<N> vis, ans;
queue<int> qq;
bool check()
{
    for(int i = 1; i <= n; i ++ )
        if(din[i] < 2)
        {
            vis[i] = true;
            qq.push(i);
        }
    while(qq.size())
    {
        int u = qq.front();
        qq.pop();
        for(int i = hs[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            din[v] --;
            if(!vis[v] && din[v] < 2) 
            {
                qq.push(v);
                vis[v] = true;
            }
        }
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            din[v] --;
            if(!vis[v] && din[v] < 2) 
            {
                qq.push(v);
                vis[v] = true;
            }
        }
    }

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            return false;
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(h, a, b), add(h, b, a);
        din[a] ++, din[b] ++;
    }

    dfs1(1, 1);
    dfs2(1, 1);

    kth::dfs1(1, 1);
    kth::dfs2(1, 1);

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        if(in_son(b, a))
        {
            int v = kth::kthfa(b, dep[b] - dep[a] - 1);
            c[1] ++, c[dfn[v]] --;
            c[dfn[v] + siz[v]] ++, c[n + 1] --;
        }
        else
        {
            c[dfn[a]] ++, c[dfn[a] + siz[a]] --;
        }
        add(hs, a, b);
        din[b] ++;
    }

    if(!check())
    {
        cerr << "yeah" << endl;
        for(int i = 1; i <= n; i ++ )
            printf("0\n");
        return 0;
    }

    for(int i = 1; i <= n; i ++ )
    {
        c[i] += c[i - 1];
        if(c[i] == 0) ans[anti[i]] = 1;
    }

    for(int i = 1; i <= n; i ++ )
        if(ans[i]) puts("1");
        else puts("0");

    return 0;
}
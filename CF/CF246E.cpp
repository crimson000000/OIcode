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

const int N = 1e6 + 10, mod = 998244353, P = 131;
int h[N], e[N], ne[N], idx;
int v[N];
string s[N];
int n, m;

struct query
{
    int id, k;
    bool operator < (const query& a) const
    {
        return k < a.k;
    }
};

set<string> t[N * 2];
vector<query> q[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int ans[N];
int son[N], siz[N], dep[N], fa[N];
void dfs1(int u, int f)
{
    siz[u] = 1, dep[u] = dep[f] + 1;
    fa[u] = f;
    int maxsize = -1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        dfs1(j, u);
        siz[u] += siz[j];
        if(siz[j] > maxsize)
        {
            maxsize = siz[j];
            son[u] = j;
        }
    }
}

void del(int u)
{
    t[dep[u]].clear();
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        del(j);
    }
}

inline void update(int x)
{
    t[dep[x]].insert(s[x]);
}

void add(int u)
{
    update(u);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        add(j);
    }
}

bitset<N> vis;
void dsu(int u)
{
    vis[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == son[u]) continue;
        dsu(j);
        del(j);
    }
    if(son[u]) dsu(son[u]);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j != son[u])
            add(j);
    }
    update(u);
    for(auto i : q[u])
    {
        int id = i.id, k = i.k;
        ans[id] = t[k].size();
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
    for(int i = 1; i <= n; i ++ )
    {
        cin >> s[i];
        int x = read();
        if(x) add(x, i);
    }

    for(int i = 1; i <= n; i ++ )
        if(!dep[i])
            dfs1(i, i);
    
    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int u = read(), k = read();
        q[u].push_back({i, k + dep[u]});
    }

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            dsu(i), del(i);

    for(int i = 1; i <= m; i ++ )
        printf("%d\n", ans[i]);

    return 0;
}
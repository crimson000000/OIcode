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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;

namespace rnd
{
    #define ui unsigned int
    ui s;

    inline ui get(ui x) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return s = x; 
    }
}

int n, q;
int root;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dep[N], mdep[N], son[N], fa[N];
void dfs1(int u, int f)
{
    dep[u] = dep[f] + 1, fa[u] = f;
    mdep[u] = dep[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        if(mdep[j] > mdep[u])
        {
            mdep[u] = mdep[j];
            son[u] = j;
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

int lastans;
ll ans;

int ancestor(int x, int k)
{
    while(k)
    {
        if(dfn[x] - dfn[top[x]] < k)
        {
            k -= dfn[x] - dfn[top[x]] + 1;
            x = fa[top[x]];
        }
        else return anti[dfn[x] - k];
    }
    return x;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), q = read();
    cin >> rnd::s;
    for(int i = 1; i <= n; i ++ )
    {
        int f = read();
        if(f == 0) root = i;
        else add(f, i), add(i, f);
    }

    dfs1(root, root);
    dfs2(root, root);

    for(int i = 1; i <= q; i ++ )
    {
        int x = (rnd::get(rnd::s) ^ lastans) % n + 1;
        int k = (rnd::get(rnd::s) ^ lastans) % dep[x];
        lastans = ancestor(x, k);
        ans ^= (ll)i * lastans;
    }

    cout << ans << endl;
    
    return 0;
}

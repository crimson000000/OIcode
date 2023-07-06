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
int ans[N], deg[N];
int n, su;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bitset<N> vis;
void dfs(int u)
{
    for(int &i = h[u]; i != -1; i = ne[i])
    {
        if(vis[i]) continue;
        int v = e[i];
        if(v == u + n) ans[u] = 1;
        else if(u == v + n) ans[v] = -1;
        vis[i] = vis[i ^ 1] = true;
        dfs(v);
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
    su = n * 2 + 2;
    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        if(x == -1) add(su, i), add(i, su), deg[i] ++;
        else 
        {
            add(x, i), add(i, x);
            deg[i] ++, deg[x] ++;
        }
    }

    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        if(x == -1) add(su, i + n), add(i + n, su), deg[i + n] ++;
        else 
        {
            add(x + n, i + n), add(i + n, x + n);
            deg[x + n] ++, deg[i + n] ++;
        }
    }

    for(int i = 1; i <= n; i ++ )
        if((deg[i] & 1) != (deg[i + n] & 1))
        {
            puts("IMPOSSIBLE");
            return 0;
        }

    for(int i = 1; i <= n; i ++ )
        if(deg[i] & 1)
            add(i + n, i), add(i, i + n);

    puts("POSSIBLE");
    dfs(su);

    for(int i = 1; i <= n; i ++ ) printf("%d ", ans[i]);

    return 0;
}
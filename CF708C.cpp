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
int dp[N][2], ans[N], dpp[N];
int siz[N];
int maxsiz[N], pos[N];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs1(int u, int fa)
{
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];

        if(siz[v] > siz[maxsiz[u]]) maxsiz[u] = v;

        int newdp = dp[v][0];
        if(siz[v] <= n / 2) newdp = max(dp[v][0], siz[v]);
        
        if(newdp > dp[u][0]) dp[u][1] = dp[u][0], dp[u][0] = newdp, pos[u] = v;
        else if(newdp > dp[u][1]) dp[u][1] = newdp;
    }
}

void dfs2(int u, int fa)
{
    ans[u] = 1;
    if(siz[maxsiz[u]] > n / 2) ans[u] = (siz[maxsiz[u]] - dp[maxsiz[u]][0] <= n / 2);
    else if(n - siz[u] > n / 2) ans[u] = (n - siz[u] - dpp[u] <= n / 2);

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;

        int newdp = 0;
        if(n - siz[v] <= n / 2) newdp = n - siz[v];
        newdp = max(newdp, dpp[u]);

        dpp[v] = max(dpp[v], newdp);
        if(pos[u] == v) dpp[v] = max(dpp[v], dp[u][1]);
        else dpp[v] = max(dpp[v], dp[u][0]);
        dfs2(v, u);
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    for(int i = 1; i <= n; i ++ ) printf("%d ", ans[i]);

    return 0;
}
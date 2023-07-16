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

const int N = 1e6 + 10, M = 1010;
vector<int> g[N];
int a[N], b[N];
int deg[N];
int vis[N];
ll ans;
int n, m;

inline void add(int a, int b)
{
    g[a].emplace_back(b);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        a[i] = read(), b[i] = read();
        deg[a[i]] ++;
        deg[b[i]] ++;
    }

    for(int i = 1; i <= m; i ++ )
    {
        if(deg[a[i]] > deg[b[i]] || (deg[a[i]] == deg[b[i]] && a[i] < b[i])) 
            swap(a[i], b[i]);
        add(b[i], a[i]);
    }

    for(int u = 1; u <= n; u ++ )
    {
        for(auto v : g[u]) vis[v] = u;
        for(auto v : g[u])
            for(auto w : g[v])
                if(vis[w] == u)
                    ans ++;
    }

    cout << ans << endl;

    return 0;
}
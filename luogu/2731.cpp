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

const int N = 1510;
vector<int> G[N];
int tmp[N];
map<PII, int> mp;
int n, m;
int din[N];
int stk[N], tt;

void dfs(int u)
{
    for(; tmp[u] < (int)G[u].size(); tmp[u] ++ )
    {
        int v = G[u][tmp[u]];
        if(!mp[{u, v}]) continue;
        mp[{u, v}] --, mp[{v, u}] --;
        dfs(v);
    }
    stk[++ tt] = u;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        n = max(a, n);
        n = max(b, n);
        G[a].push_back(b);
        G[b].push_back(a);
        mp[{a, b}] ++;
        mp[{b, a}] ++;
        din[a] ++;
        din[b] ++;
    }

    for(int i = 1; i <= n; i ++ ) sort(G[i].begin(), G[i].end());

    for(int i = 1; i <= n; i ++ )
        if(din[i] & 1)
        {
            dfs(i);
            while(tt > 0) printf("%d\n", stk[tt -- ]);
            return 0;
        }

    dfs(1);
    while(tt > 0) printf("%d\n", stk[tt -- ]);

    return 0;
}
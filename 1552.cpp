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
priority_queue<ll> root[N];
ll cost[N];
int rt;
int h[N], e[N], ne[N], idx;
ll c[N], l[N];
ll ans;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void merge(int x, int y)
{
    if(root[x].size() > root[y].size()) swap(root[x], root[y]);
    while(root[x].size())
    {
        root[y].push(root[x].top());
        root[x].pop();
    }
}

void dfs(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u);
        merge(j, u);
        cost[u] += cost[j];
    }

    root[u].push(c[u]);
    cost[u] += c[u];

    while(cost[u] > m)
    {
        cost[u] -= root[u].top();
        root[u].pop();
    }

    ans = max(ans, l[u] * (ll)root[u].size());
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        int x = read();
        c[i] = read(), l[i] = read();
        if(x) add(i, x), add(x, i);
        else rt = i;
    }

    dfs(rt, 0);

    cout << ans << endl;

    return 0;
}
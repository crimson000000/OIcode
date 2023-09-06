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

const int N = 1e6 + 10, mod = 998244353;
vector<int> G1[N], G2[N];
int n, m, q;
ll a[N];
ll add[N], pos[N], mul[N], cnt[N];
int op[N];

bitset<N> vis;
inline ll dfs(int u)
{
    if(vis[u]) return mul[u];
    vis[u] = true;
    for(auto v : G1[u])
    {
        mul[u] = mul[u] * dfs(v) % mod;
        // cout << u << ' ' << v << ' ' << dfs(v) << endl;
    }
    return mul[u];
}

int deg[N];
inline void topsort()
{
    queue<int> q;
    for(int i = 0; i <= m; i ++ )
    {
        if(!deg[i]) q.push(i);
    }

    while(q.size())
    {
        int u = q.front();
        q.pop();

        ll M = 1;
        for(int i = G1[u].size(); i; i -- )
        {
            int v = G1[u][i - 1];
            cnt[v] = (cnt[v] + cnt[u] * M % mod) % mod;
            M = M * mul[v] % mod;
            deg[v] --;
            if(!deg[v]) q.push(v);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        op[i] = read();
        if(op[i] == 1)
        {
            pos[i] = read();
            add[i] = read();
            mul[i] = 1;
        }
        else if(op[i] == 2)
        {
            mul[i] = read();
        }
        else
        {
            mul[i] = 1;
            int cnt = read();
            while(cnt -- )
            {
                int x = read();
                G1[i].push_back(x);
                deg[x] ++;
            }
        }
    }

    q = read();
    cnt[0] = 1;
    mul[0] = 1;
    for(int i = 1; i <= q; i ++ )
    {
        int x = read();
        G1[0].push_back(x);
        deg[x] ++;
    }

    dfs(0);
    topsort();

    // cout << mul[0] << endl;

    for(int i = 1; i <= n; i ++ )
        a[i] = a[i] * mul[0] % mod;
    
    for(int i = 1; i <= m; i ++ )
    {
        if(op[i] == 1)
        {
            a[pos[i]] = (a[pos[i]] + add[i] * cnt[i] % mod) % mod;
        }
    }

    for(int i = 1; i <= n; i ++ ) printf("%lld ", a[i] % mod);

    return 0;
}
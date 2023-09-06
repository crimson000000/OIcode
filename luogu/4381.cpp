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

const int N = 2e6 + 10;
int e[N], w[N];
int din[N];
int n;
queue<int> q;
ll f[N], g[N];
ll ans;

ll solve(int u)
{
    int st = u;
    ll pre = w[u];
    ll ret1 = g[u], ret2 = -0x3f3f3f3f3f3f3f3f;
    ll m1 = f[u], m2 = f[u];
    // cout << u << endl;
    u = e[u];
    while(u != st)
    {
        din[u] = 0;
        // cout << u << endl;
        ret1 = max(ret1, f[u] + pre + m1);
        ret2 = max(ret2, f[u] - pre + m2);
        ret1 = max(ret1, g[u]);
        m1 = max(m1, f[u] - pre);
        m2 = max(m2, f[u] + pre);
        pre += w[u];
        u = e[u];
    }
    return max(ret1, ret2 + pre);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        e[i] = read();
        w[i] = read();
        din[e[i]] ++;
    }

    for(int i = 1; i <= n; i ++ )
        if(!din[i])
            q.push(i);
    
    while(q.size())
    {
        int u = q.front();
        q.pop();
        
        ll maxn = f[u] + w[u];
        g[e[u]] = max(g[e[u]], f[e[u]] + maxn);
        g[e[u]] = max(g[e[u]], g[u]);
        f[e[u]] = max(f[e[u]], maxn);
        din[e[u]] --;
        if(!din[e[u]]) q.push(e[u]);
    }

    for(int i = 1; i <= n; i ++ )
        if(din[i])
            ans += solve(i);

    cout << ans << endl;

    return 0;
}
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

const int N = 1e6 + 10, mod = 998244353;
int h[N], e[N], ne[N], idx;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfn[N], stk[N], tt, tim;
int low[N];
bitset<N> flg, vis;
int id[N];
ll ans;
bool is_shanben;
int dcnt;

inline void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u;
    bool flag = false;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        if(!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] < dfn[u])
            {
                if(!flag) flag = true;
                else is_shanben = false;
            }
        }
        else 
        {
            low[u] = min(low[u], dfn[v]);
            if(low[v] < dfn[u])
            {
                if(!flag) flag = true;
                else is_shanben = false;
            }
        }
    }

    if(low[u] == dfn[u])
    {
        int y;
        do {
            y = stk[tt -- ];
            id[y] = u;
        } while(y != u);
    }
}

ll f[N], g[N], H[N];
inline void dp(int u, int fa)
{
    int ch = 0;
    vis[u] = true;
    f[u] = 1, g[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || flg[i]) continue;
        dp(v, u);
        ch ++;
        f[u] = f[u] * g[v] % mod;
    }
    g[u] = (f[u] * H[ch] % mod + f[u] * H[ch - 1] % mod * ch % mod) % mod;
    f[u] = f[u] * H[ch] % mod;
}

inline void startdp()
{
    for(int i = 0; i <= idx; i ++ )
    {
        int v = e[i], u = e[i ^ 1];
        if(id[v] == id[u])
            flg[i] = true;
    }

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            dp(i, 0);
            ans = ans * f[i] % mod;
        }
}

inline void init()
{
    for(int i = 0; i <= n; i ++ ) 
    {
        h[i] = -1;
        dfn[i] = low[i] = 0;
        vis[i] = false;
        id[i] = 0;
        stk[i] = 0;
    }
    for(int i = 0; i <= idx; i ++ ) flg[i] = false;
    is_shanben = true;
    idx = dcnt = tt = tim = 0;
    ans = 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    H[0] = H[1] = 1;
    for(int i = 2; i <= N - 5; i ++ ) 
        H[i] = ((i - 1) * H[i - 2] % mod + H[i - 1]) % mod;

    int T = read();
    while(T -- )
    {
        init();

        n = read(), m = read();
        for(int i = 1; i <= m; i ++ )
        {
            int a = read(), b = read();
            add(a, b), add(b, a);
        }

        tarjan(1, 1);
        if(!is_shanben)
        {
            puts("0");
            continue;
        }

        startdp();
        printf("%lld\n", ans);
    }

    return 0;
}

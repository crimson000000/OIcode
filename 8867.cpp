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

const int N = 3e6 + 10, mod = 1e9 + 7;
int h[N], e[N], ne[N], idx;
int hs[N];
ll f[N][2];
int n, m;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfn[N], low[N], tim;
int stk[N], tt;
bitset<N> in_stk;
int id[N], scc_cnt;
int s[N];
struct scc
{
    int e, v;
}sc[N];

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u, in_stk[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        if(!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if(in_stk[v]) 
            low[u] = min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u])
    {
        scc_cnt ++;
        int y;
        do {
            y = stk[tt -- ];
            in_stk[y] = false;
            sc[scc_cnt].v ++;
            id[y] = scc_cnt;
        } while(u != y);
    }
}

void dfs1(int u, int fa)
{
    s[u] = sc[u].e;
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        s[u] += s[v] + 1;
    }
}

ll ans;
void dp(int u, int fa)
{
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dp(v, u);
        f[u][1] = (f[u][0] * f[v][1] % mod + (2 * f[v][0] + f[v][1]) % mod * f[u][1] % mod) % mod;
        f[u][0] = f[u][0] * ((f[v][0] << 1) % mod) % mod;
    }
    if(u == 1) ans = (ans + f[u][1]) % mod;
    else ans = (ans + f[u][1] * qmi(2, s[1] - s[u] - 1, mod) % mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(h, a, b), add(h, b, a);
    }

    tarjan(1, 0);
    
    for(int u = 1; u <= n; u ++ )
    {
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(id[u] == id[v]) sc[id[u]].e ++;
            else add(hs, id[u], id[v]);
        }
    }

    for(int i = 1; i <= scc_cnt; i ++ ) 
    {
        sc[i].e >>= 1;
        f[i][0] = qmi(2, sc[i].e, mod);
        f[i][1] = qmi(2, sc[i].e + sc[i].v, mod) - f[i][0];
    }

    dfs1(1, 1);
    dp(1, 1);

    cout << (ans % mod + mod) % mod << endl;

    return 0;
}
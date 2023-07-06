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

const int N = 1000 + 10, mod = 1e9 + 7;
int h[N], e[N], ne[N], idx;
int din[N];
ll C[N][N];
ll f[N][N];
int in[N];
bitset<N> isin;
int n, m;

int p[N];
inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline int merge(int x, int y)
{
    x = find(x), y = find(y);
    if(x != y) p[x] = y;
    else return 1;
    return 0;
}

struct know
{
    int x, y;
    bool equ;
}kow[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void init(int n)
{
    for(int i = 0; i <= n; i ++ ) C[i][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

int siz[N];
ll g[N];
void dfs(int u, int fa)
{
    f[u][1] = 1;
    siz[u] = 1;
    for(int ii = h[u]; ii != -1; ii = ne[ii])
    {
        int v = e[ii];
        if(v == fa) continue;
        dfs(v, u);
        for(int i = 1; i <= n; i ++ ) g[i] = 0;
        for(int i = 1; i <= siz[u] + siz[v]; i ++ )
            for(int j = 1; j <= siz[u]; j ++ )
                for(int k = 1; k <= siz[v]; k ++ )
                {
                    int x = k - i + j;
                    if(x < 0) continue;
                    g[i] = (g[i] + f[u][j] * f[v][k] % mod * (C[i - 1][j - 1] * C[j - 1][x] % mod) % mod) % mod; 
                }
        for(int i = 1; i <= siz[u] + siz[v]; i ++ ) f[u][i] = g[i];
        siz[u] += siz[v];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();

    for(int i = 1; i <= n + 1; i ++ ) p[i] = i;
    init(n * 2);
    
    for(int i = 1; i <= m; i ++ )
    {
        kow[i].x = read();
        char s[5];
        scanf("%s", s);
        kow[i].y = read();
        if(s[0] == '=') 
        {
            kow[i].equ = true;
        }
    }

    for(int i = 1; i <= m; i ++ )
    {
        if(kow[i].equ)
            merge(kow[i].x, kow[i].y);
    }

    for(int i = 1; i <= n; i ++ ) isin[in[i] = find(i)] = true;

    for(int i = 1; i <= n + 1; i ++ ) p[i] = i;

    for(int i = 1; i <= m; i ++ )
        if(!kow[i].equ)
        {
            add(in[kow[i].x], in[kow[i].y]), add(in[kow[i].y], in[kow[i].x]);
            din[in[kow[i].y]] ++;
            if(merge(in[kow[i].x], in[kow[i].y]))
            {
                puts("0");
                return 0;
            }
        }

    for(int i = 1; i <= n; i ++ )
        if(isin[i] && !din[i])
            add(n + 1, i), add(i, n + 1);

    dfs(n + 1, n + 1);

    ll ans = 0;
    for(int i = 1; i <= siz[n + 1]; i ++ ) ans = (ans + f[n + 1][i]) % mod;

    cout << ans << endl;

    return 0;
}

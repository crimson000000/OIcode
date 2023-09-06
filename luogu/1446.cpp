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

const int N = 60 + 10;
int p[N];
ll f[N][N][N];
int sa, sb, sg;
int n, m, mod;
ll ans;
int tot;

bitset<N> vis;
int siz[N];

inline void dfs(int u)
{
    if(vis[u]) return;
    vis[u] = 1;
    siz[tot] ++;
    dfs(p[u]);
}

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

inline ll calc()
{
    vis.reset();
    memset(siz, 0, sizeof siz);
    tot = 0;
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            tot ++;
            dfs(i);
        }
        
    // for(int i = 1; i <= tot; i ++ ) cout << siz[i] << ' ';
    // puts("");

    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    int sum = 0;
    for(int i = 1; i <= tot; i ++ )
    {
        sum += siz[i];
        for(int a = 0; a <= sa; a ++ )
            for(int b = 0; b <= sb; b ++ )
            {
                int c = sum - a - b;
                if(c < 0 || c > sg) continue;
                if(a >= siz[i]) f[i][a][b] = (f[i][a][b] + f[i - 1][a - siz[i]][b]) % mod;
                if(b >= siz[i]) f[i][a][b] = (f[i][a][b] + f[i - 1][a][b - siz[i]]) % mod;
                if(c >= siz[i]) f[i][a][b] = (f[i][a][b] + f[i - 1][a][b]) % mod;
            } 
    }

    return f[tot][sa][sb];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    sa = read(), sb = read(), sg = read();
    n = sa + sb + sg;
    
    m = read(), mod = read();
    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 1; j <= n; j ++ ) p[j] = read();
        ans = (ans + calc()) % mod;
    }

    for(int i = 1; i <= n; i ++ ) p[i] = i;
    ans = (ans + calc()) % mod;

    cout << ans * qmi(m + 1, mod - 2, mod) % mod << endl;

    return 0;
}

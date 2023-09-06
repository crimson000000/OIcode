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

const int N = 2e6 + 10, mod = 998244353;
int l[N], r[N];
ll cat[N], f[N];
int siz[N];
bool fa[N];
int n;

ll qmi(ll a, ll k, ll p)
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

void init(int n)
{
    cat[0] = cat[1] = 1;
    for(int i = 2; i <= n; i ++ ) 
        cat[i] = (4ll * i - 2) % mod * qmi(i + 1, mod - 2, mod) % mod * cat[i - 1] % mod;
}

inline ll add(ll a, ll b)
{
    ll ret = a + b;
    while(ret >= mod) ret -= mod;
    return ret;
}

inline ll sub(ll a, ll b)
{
    ll ret = a - b;
    while(ret < 0) ret += mod;
    return ret;
}

void dfs_siz(int u)
{
    siz[u] = 1;
    if(l[u]) dfs_siz(l[u]);
    if(r[u]) dfs_siz(r[u]);
    siz[u] += siz[l[u]];
    siz[u] += siz[r[u]];
}

void dfs(int u)
{
    if(!l[u] && !r[u]) return;
    if(l[u]) dfs(l[u]);
    if(r[u]) dfs(r[u]);
    f[u] = (f[u] + f[r[u]]) % mod;
    f[u] = (f[u] + f[l[u]] * cat[siz[r[u]]]) % mod;
    if(siz[l[u]] <= siz[r[u]])
    {
        for(int i = 0; i < siz[l[u]]; i ++ )
            f[u] = (f[u] + cat[i] * cat[siz[u] - i - 1] % mod) % mod;
    }
    else
    {
        f[u] = (f[u] + cat[siz[u]]) % mod;
        for(int i = siz[l[u]]; i < siz[u]; i ++ )
            f[u] = (f[u] - cat[i] * cat[siz[u] - i - 1] % mod + mod) % mod;
    }
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
        l[i] = read(), r[i] = read();
        fa[l[i]] = fa[r[i]] = true;
    }

    init(n + 2);

    int root = 0;
    for(int i = 1; i <= n; i ++ ) 
        root = fa[i] ? root : i;

    dfs_siz(root);

    dfs(root);
    for(int i = 1; i < n; i ++ )
        f[root] += cat[i];

    cout << f[root] % mod << endl;

    return 0;
} 

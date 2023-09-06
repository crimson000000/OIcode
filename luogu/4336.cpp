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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 20, mod = 1e9 + 7;
ll f[N];
int n;
struct edge
{
    int a, b;
};

struct comp
{
    vector<edge> p;
}c[N];

struct matrix
{
    ll a[N][N];
    inline void init()
    {
        memset(a, 0, sizeof a);
    }

    inline void build(vector<edge> E)
    {
        init();
        for(auto e : E)
        {
            int u = e.a, v = e.b;
            a[u][v] = (a[u][v] - 1 + mod) % mod;
            a[v][u] = (a[v][u] - 1 + mod) % mod;
            a[u][u] ++;
            a[v][v] ++;
        }
    }

    inline ll Det(int n)
    {
        ll res = 1, w = 1;
        for(int i = 1; i <= n; i ++ )
        {
            for(int j = i + 1; j <= n; j ++ )
            {
                while(a[i][i])
                {
                    ll div = a[j][i] / a[i][i];
                    for(int k = i; k <= n; k ++ )
                        a[j][k] = (a[j][k] - div * a[i][k] % mod + mod) % mod;
                    swap(a[i], a[j]);
                    w = -w;
                }
                swap(a[i], a[j]);
                w = -w;
            }
        }
        for(int i = 1; i <= n; i ++ ) res = res * a[i][i] % mod;
        res *= w;
        return (res % mod + mod) % mod;
    }
}L;
vector<edge> E;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int cnt = read();
        while(cnt -- )
        {
            int a = read(), b = read();
            c[i].p.push_back({a, b});
        }
    }

    for(int i = 0; i < (1 << n - 1); i ++ )
    {
        int cnt = 0;
        E.clear();
        for(int j = 0; j < n - 1; j ++ )
            if(i >> j & 1)
            {
                cnt ++;
                for(auto u : c[j + 1].p)
                    E.emplace_back(u);
            }

        L.build(E);
        f[cnt] = (f[cnt] + L.Det(n - 1)) % mod;
    }

    // for(int i = 0; i <= n; i ++ ) cout << f[i] << ' ';
    // puts("");

    ll ans = 0;
    for(int i = 0; i < n; i ++ )
        ans = (ans + (((n - i - 1) & 1) ? mod - 1 : 1) * f[i] % mod) % mod;

    cout << ans << endl;

    return 0;
}
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

const int N = 12, mod = 1e9 + 7;
ll fact[N], invfact[N];
ll f[N][N];
int b[N], c[N];
int num[N];
int n, a[N];
ll g[N];
ll h[N];
ll ans;

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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    ll ans = invfact[m];
    for(int i = n - m + 1; i <= n; i ++ )
        ans = ans * i % mod;
    return ans;
}

inline ll work()
{
    memset(h, 0x3f, sizeof h);
    ll m = 0;
    for(int i = 1; i <= n; i ++ )
    {
        h[b[i]] = min(h[b[i]], (ll)a[i]);
        m = max(m, (ll)b[i]);
    }

    int tot = 0;
    for(int i = 1; i <= m; i ++ )
        num[++ tot] = h[i];
    num[++ tot] = 0;

    sort(num + 1, num + 1 + tot);
    tot = unique(num + 1, num + tot + 1) - num - 1;
    
    for(int i = 1; i <= m; i ++ )
        h[i] = lower_bound(num + 1, num + tot + 1, h[i]) - num;

    memset(f, 0, sizeof f);
    f[0][1] = 1;
    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 2; j <= h[i]; j ++ )
        {
            ll minn = h[i];
            for(int k = i; k; k -- )
            {
                minn = min(minn, h[k]);
                if(j > minn) break;
                for(int x = 1; x < j; x ++ )
                {
                    f[i][j] = (f[i][j] + C(num[j] - num[j - 1], i - k + 1) * f[k - 1][x] % mod) % mod;
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 2; i <= tot; i ++ )
        ans = (ans + f[m][i]) % mod;
    return ans;
}

inline void dfs(int now)
{
    if(now == n + 1)
    {
        for(int i = 1; i <= n; i ++ ) c[i] = b[i];
        for(int i = 1; i <= n; i ++ ) cout << b[i] << ' ';
        puts("");
        sort(c + 1, c + n + 1);
        for(int i = 1; i <= n; i ++ )
            if(c[i] - c[i - 1] > 1) return;
        
        ll mx = 0;
        for(int i = 1; i <= n; i ++ )
        {
            g[i] = 1;
            for(int j = 1; j < i; j ++ )
                if(b[j] < b[i])
                    g[i] = max(g[i], g[j] + 1);
            mx = max(mx, g[i]);
        }

        cout << mx << endl;

        ans = (ans + work() * mx % mod) % mod;

        cout << work() << endl;

        return;
    }
    for(int i = 1; i <= n; i ++ ) 
    {
        b[now] = i;
        dfs(now + 1);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(n);
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    dfs(1);

    for(int i = 1; i <= n; i ++ ) ans = ans * qmi(a[i], mod - 2, mod) % mod;

    cout << ans << endl;

    return 0;
}
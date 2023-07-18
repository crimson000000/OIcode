// Problem: E - Random LIS
// Contest: AtCoder - AtCoder Regular Contest 104
// URL: https://atcoder.jp/contests/arc104/tasks/arc104_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 12;
const ll mod = 1000000007;

inline ll qpow(ll b, ll p)
{
    ll res = 1;
    while (p)
    {
        if (p & 1)
        {
            res = res * b % mod;
        }
        b = b * b % mod;
        p >>= 1;
    }
    return res;
}

ll n, fac[maxn], ifac[maxn], a[maxn], b[maxn], c[maxn], g[maxn], ans;
ll h[maxn], lsh[maxn], f[maxn][maxn];

inline ll C(ll n, ll m)
{
    if (n < m || n < 0 || m < 0)
    {
        return 0;
    }
    else
    {
        ll ans = ifac[m];
        for (int i = 0; i < m; ++i)
        {
            ans = ans * (n - i) % mod;
        }
        return ans;
    }
}

inline ll work()
{
    mems(h, 0x3f);
    ll m = 0;
    for (int i = 1; i <= n; ++i)
    {
        h[b[i]] = min(h[b[i]], a[i]);
        m = max(m, b[i]);
    }
    int tot = 0;
    for (int i = 1; i <= m; ++i)
    {
        lsh[++tot] = h[i];
    }
    lsh[++tot] = 0;
    sort(lsh + 1, lsh + tot + 1);
    tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1;
    for (int i = 1; i <= m; ++i)
    {
        h[i] = lower_bound(lsh + 1, lsh + tot + 1, h[i]) - lsh;
    }
    mems(f, 0);
    f[0][1] = 1;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 2; j <= h[i]; ++j)
        {
            // printf("%d %d\n", i, j);
            ll mn = h[i];
            for (int k = i; k; --k)
            {
                mn = min(mn, h[k]);
                if (j > mn)
                {
                    break;
                }
                for (int x = 1; x < j; ++x)
                {
                    if (!f[k - 1][x])
                    {
                        continue;
                    }
                    f[i][j] = (f[i][j] + C(lsh[j] - lsh[j - 1], i - k + 1) * f[k - 1][x] % mod) % mod;
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 2; i <= tot; ++i)
    {
        ans = (ans + f[m][i]) % mod;
    }
    // if (ans) {
    // printf("b: ");
    // for (int i = 1; i <= n; ++i) {
    // printf("%lld ", b[i]);
    // }
    // putchar('\n');
    // printf("h: ");
    // for (int i = 1; i <= m; ++i) {
    // printf("%lld ", h[i]);
    // }
    // putchar('\n');
    // printf("%lld\n", ans);
    // }
    return ans;
}

void dfs(int d)
{
    if (d > n)
    {
        for (int i = 1; i <= n; ++i)
        {
            c[i] = b[i];
        }
        sort(c + 1, c + n + 1);
        for (int i = 1; i <= n; ++i)
        {
            if (c[i] - c[i - 1] > 1)
            {
                return;
            }
        }
        ll mx = 0;
        for (int i = 1; i <= n; ++i)
        {
            g[i] = 1;
            for (int j = 1; j < i; ++j)
            {
                if (b[j] < b[i])
                {
                    g[i] = max(g[i], g[j] + 1);
                }
            }
            mx = max(mx, g[i]);
        }
        ans = (ans + mx * work() % mod) % mod;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        b[d] = i;
        dfs(d + 1);
    }
}

void solve()
{
    scanf("%lld", &n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; ~i; --i)
    {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    dfs(1);
    // printf("ans: %lld\n", ans);
    for (int i = 1; i <= n; ++i)
    {
        ans = ans * qpow(a[i], mod - 2) % mod;
    }
    printf("%lld\n", ans);
}

int main()
{
    int T = 1;
    // scanf("%d", &T);
    while (T--)
    {
        solve();
    }
    return 0;
}

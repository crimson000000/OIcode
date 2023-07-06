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

const int N = 1e6, K = 20, mod = 1e9 + 7;
int l[N][K], r[N][K];
int w[N], c[N], d[N], e[N];
ll f[K][N], h[N];
int a[N], b[N];
int n, m;
ll ans;

inline bool nosolution()
{
    bool flag = true;
    for(int i = 1; i <= m; i ++ )
    {
        if(e[i] != 0 || r[n][i] - l[n][i] >= w[i])
            flag = false;
    }
    return flag;
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

ll F[N];
inline ll calc(ll n, ll k)
{
    if(n <= k + 2)
    {
        ll res = 0;
        for(int i = 1; i <= n; i ++ )
            res = (res + qmi(i, k, mod)) % mod;
        return res;
    }
    for(int i = 1; i <= k + 2; i ++ ) F[i] = qmi(i, k, mod);
    for(int i = 1; i <= k + 2; i ++ ) F[i] = (F[i] + F[i - 1]) % mod;
    ll res = 0;
    for(int i = 1; i <= k + 2; i ++ )
    {
        ll tmp = F[i];
        for(int j = 1; j <= k + 2; j ++ )
        {
            if(j == i) continue;
            tmp = tmp * (n - j) % mod * qmi(i - j, mod - 2, mod) % mod;
        }
        res += tmp;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ ) w[i] = read();
    for(int i = 1; i <= n; i ++ )
    {
        c[i] = read(), d[i] = read();
        e[c[i]] += d[i];
        for(int j = 1; j <= m; j ++ )
        {
            l[i][j] = l[i - 1][j];
            r[i][j] = r[i - 1][j];
        }
        l[i][c[i]] = min(l[i][c[i]], e[c[i]]);
        r[i][c[i]] = max(r[i][c[i]], e[c[i]]);
    }

    if(nosolution())
    {
        puts("-1");
        return 0;
    }

    for(int i = 1; i <= n; i ++ ) a[i] = w[i] - (r[n][i] - l[n][i]);

    for(int i = 0; i <= n; i ++ )
    {
        ll s = 1;
        for(int j = 1; j <= m; j ++ )
            s = s * max(0, w[j] - (r[i][j] - l[i][j])) % mod;
        ans = (ans + s) % mod;
    } 

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            l[i][j] = min(0, l[i][j] + e[j] - l[n][j]);
            r[i][j] = max(0, r[i][j] + e[j] - r[n][j]);
        }

    for(int i = 1; i <= m; i ++ ) b[i] = r[n][i] - l[n][i];

    int last = -1;
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 0; j <= m; j ++ ) f[0][j] = 0;
        f[0][0] = 1;
        int t = 0x3f3f3f3f;
        for(int j = 1; j <= m; j ++ )
        {
            int x = a[j] - (r[i][j] - l[i][j]);
            if(x <= 0) goto fuckccf;
            if(b[j] > 0) t = min(t, x / b[j]);
            for(int k = 0; k <= m; k ++ )
            {
                f[j][k] = f[j - 1][k] * x % mod;
                if(k > 0) f[j][k] = (f[j][k] + f[j - 1][k - 1] * (-b[j])) % mod;
            }
        }
        ans = (ans + f[m][0] * (t + 1) % mod) % mod;
        if(t != last)
        {
            last = t;
            for(int j = 1; j <= m; j ++ ) h[j] = calc(t, j);
        }
        for(int j = 1; j <= m; j ++ )
            ans = (ans + h[j] * f[m][j] % mod) % mod;
    }

    fuckccf:;

    cout << (ans % mod + mod) % mod << endl;

    return 0;
}
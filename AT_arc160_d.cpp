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

const int mod = 998244353, N = 10010;
ll inv[N];
ll n, m, ans, k;

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

inline void init(int n)
{
    inv[1] = 1;
    for(int i = 2; i <= n; i ++ )
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
}

inline ll C(ll n, ll m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    ll res = 1;
    for(ll i = n - m + 1; i <= n; i ++ )
        res = res * (i % mod) % mod;
    for(int i = 1; i <= m; i ++ )
        res = res * inv[i] % mod;
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    if(m % k)
    {
        puts("0");
        return 0;
    }

    init(2 * n);

    for(int i = 0; i <= n - k + 1; i ++ )
    {
        ans = (ans + ((i & 1) ? -1 : 1) * C(n - k + 1, i) * C(m / k - i * k + 2 * n - k, 2 * n - k) % mod + mod) % mod;
    }

    cout << ans << endl;

    return 0;
}
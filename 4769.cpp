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
ll fact[N], invfact[N];
bool vis[N];
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
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

ll C(int n, int m)
{
    if(m > n) return 0;
    if(n < 0 || m < 0) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

ll f(int i, int j)
{
    if(i <= j && j <= n)
        return (C(2 * n - i - j - 1, n - i - 1) - C(2 * n - i - j - 1, n - j - 2) + mod) % mod;
    else return 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 2);
    int T = read();
    while(T -- )
    {
        n = read();
        bool flag = false;
        memset(vis, 0, sizeof vis);
        ll ans = 0, mx = 0, mn = 1;
        for(int i = 1; i <= n; i ++ )
        {
            int v = read();
            if(flag) continue;

            ans = (ans + f(i - 1, max(mx, (ll)v) + 1)) % mod;
            if(mx > v && v > mn) flag = true;
            mx = max(mx, (ll)v);
            vis[v] = true;
            while(vis[mn]) mn ++;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
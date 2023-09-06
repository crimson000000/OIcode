#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 998244353;
ll n, m;

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll solve(ll n)
{
    ll res = 0;
    for(ll l = 1, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        res = (res + (r - l + 1) * (n / l) % mod) % mod;
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    printf("%lld\n", (solve(m) - solve(n - 1) + mod) % mod);

    return 0;
}

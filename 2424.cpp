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

ll x, y;

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll solve(int n)
{
    ll res = 0;
    for(int l = 1, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        res += (ll)(r - l + 1) * (l + r) / 2 * (n / l);
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    x = read(), y = read();
    
    printf("%lld\n", solve(y) - solve(x - 1));

    return 0;
}

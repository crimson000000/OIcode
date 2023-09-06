#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

ll n;

ll ans;

ll sum(ll x)
{
    return x - (x / 5) - (x / 2) + (x / 10);
}

ll count(ll x)
{
    ll res = 0;
    for(ll sum2 = 1; sum2 <= x; sum2 <<= 1)
    {
        for(ll sum5 = 1; sum2 * sum5 <= x; sum5 *= 5)
            res ++;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(ll l = 1, r = 0; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (n / l) * (sum(r) - sum(l - 1)) * count(n / l);
    }

    cout << ans << endl;

    return 0;
}
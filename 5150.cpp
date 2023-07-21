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

ll n, ans = 1;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(ll i = 2; i <= n / i; i ++ )
    {
        if(n % i == 0)
        {
            int cnt = 0;
            while(n % i == 0) n /= i, cnt ++;
            ans = ans * (cnt << 1 | 1);
        }
    }

    if(n > 1) ans *= 3;

    cout << ans << endl;

    return 0;
}

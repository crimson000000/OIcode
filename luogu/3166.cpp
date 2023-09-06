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

const int N = 1010;

ll C3(ll n)
{   
    return n * (n - 1) / 2 * (n - 2) / 3;
}

ll n, m;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    n ++, m ++;
    ans = C3(n * m);

    ans -= n * C3(m) + m * C3(n);

    for(int i = 1; i <= n - 1; i ++ )
        for(int j = 1; j <= m - 1; j ++ )
            ans -= 2ll * (n - i) * (m - j) * (__gcd(i, j) - 1);

    cout << ans << endl;

    return 0;
}
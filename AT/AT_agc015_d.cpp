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

ll x, y, z;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    x = read(), y = read();
    if(x == y)
    {
        puts("1");
        return 0;
    }
    z = y;
    int j = 0;
    for(int i = 1; (1ll << i) <= y; i ++ )
    {
        if(((x >> i & 1) != (y >> i & 1)))
        {
            z >>= i;
            z <<= i;
            j = i;
        }
    }

    ans = z - x;
    ll l1 = z, r1 = z, l2 = (x | z), r2 = (z | (z - 1));
    for(int i = j - 1; i >= 0; i -- )
        if(y >> i & 1)
        {
            r1 |= (1ll << (i + 1)) - 1;
            break;
        }
    
    if(r1 < l2) ans += r1 - l1 + r2 - l2 + 2;
    else ans += r2 - l1 + 1;

    cout << ans << endl;

    return 0;
}
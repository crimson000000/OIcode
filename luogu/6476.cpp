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

ll p1, p2, k;

inline void solve()
{
    p1 = read(), p2 = read(), k = read();
    if(k == 1)
    {
        puts("NO");
        return;
    }
    ll t = __gcd(p1, p2);
    if(p1 < p2) swap(p1, p2);
    ll ans = (p1 - t - 1) / p2 + 1;
    puts(ans >= k ? "NO" : "YES");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}
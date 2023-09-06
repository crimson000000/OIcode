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

#define int ll
const int N = 1e6 + 10;
int primes[N], cnt;
bitset<N> st;
int n;
ll ans;

inline void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

inline ll phi(ll x)
{
    ll res = x;
    for(int i = 1; primes[i] <= x / primes[i]; i ++ )
    {
        if(x % primes[i] == 0)
        {
            res = res / primes[i] * (primes[i] - 1);
            while(x % primes[i] == 0) x /= primes[i];
        }
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(N - 5);
    
    for(int i = 1; i <= n / i; i ++ )
    {
        if(n % i == 0)
        {
            ans += (ll)i * phi(n / i);
            if(i * i != n) ans += (ll)n / i * phi(i);
        }
    }

    cout << ans << endl;

    return 0;
}

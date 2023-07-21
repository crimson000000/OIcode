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

const int N = 1e6 + 10;
ll g[N];
int primes[N], cnt;
bitset<N> st;
int n;

inline void init(int n)
{
    g[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            g[i] = 1ll * i * (i - 1) + 1;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0) 
            {
                g[t] = g[i] + (g[i] - g[i / primes[j]]) * primes[j] * primes[j];
                break;
            }
            g[t] = g[i] * g[primes[j]];
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    init(N - 5);
    
    while(T -- )
    {
        n = read();
        printf("%lld\n", (ll)n * (g[n] + 1) / 2);
    }

    return 0;
}

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
int miu[N];
int primes[N], cnt;
bitset<N> st;
ll k;

inline void init(int n)
{
    miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            miu[i] = -1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            int t = i * primes[j];
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                break;
            }
            miu[t] = -miu[i];
        }
    }
}

inline ll get(ll x)
{
    ll res = 0;
    for(ll d = 1; d * d <= x; d ++ )
    {
        res += miu[d] * (x / (d * d));
    }
    return res;
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
        k = read();
        ll l = 1, r = 1e10;
        while(l < r)
        {
            ll mid = l + r >> 1;
            if(get(mid) < k) l = mid + 1;
            else r = mid;
        }
        printf("%lld\n", l);
    }

    return 0;
}

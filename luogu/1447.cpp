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
int primes[N], cnt;
bitset<N> st;
ll phi[N];
ll n, m;

inline void init(int n)
{
    phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * phi[primes[j]];
        }
    }
    for(int i = 1; i <= n; i ++ ) phi[i] += phi[i - 1];
}

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    init(N - 5);

    ll ans = 0;
    for(ll l = 1, r; l <= min(n, m); l = r + 1)
    {
        r = min(getr(n, l), getr(m, l));
        ans += (phi[r] - phi[l - 1]) * (n / l) * (m / l);
    }

    cout << ans * 2 - n * m << endl;

    return 0;
}

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
unordered_map<ll, ll> s1, s2;
int primes[N], cnt;
bitset<N> st;
ll phi[N], miu[N];
ll n;

inline void init(int n)
{
    miu[1] = 1, phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            phi[i] = i - 1;
            miu[i] = -1;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                phi[t] = phi[i] * primes[j];
                break;
            }
            miu[t] = -miu[i];
            phi[t] = phi[i] * phi[primes[j]];
        }
    }
    for(int i = 1; i <= n; i ++ )
    {
        miu[i] = miu[i - 1] + miu[i];
        phi[i] = phi[i - 1] + phi[i];
    }
}

inline ll getr(ll n, ll l)
{
    return n / (n / l);
}

inline ll getmiu(ll n)
{
    if(n < N - 5) return miu[n];
    if(s1.count(n)) return s1[n];
    s1[n] = 1;
    for(ll l = 2, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        s1[n] -= (r - l + 1) * getmiu(n / l);
    }
    return s1[n];
}

inline ll getphi(ll n)
{
    if(n < N - 5) return phi[n];
    if(s2.count(n)) return s2[n];
    s2[n] = n * (n + 1) / 2;
    for(ll l = 2, r; l <= n; l = r + 1)
    {
        r = getr(n, l);
        s2[n] -= (r - l + 1) * getphi(n / l);
    }
    return s2[n];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    double st = clock();
    int T = read();
    init(N - 5);

    while(T -- )
    {
        n = read();
        printf("%lld %lld\n", getphi(n), getmiu(n));
    }

    cerr << (clock() - st) / CLOCKS_PER_SEC << endl;

    return 0;
}

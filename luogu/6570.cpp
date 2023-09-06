#define LOCAL
#include <bits/stdc++.h>

using namespace std;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

using ll = long long;
auto read = [&] ()
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
};

static const int N = 1e6 + 10, mod = 1e9 + 7;
static ll dp[N];
static int primes[N], cnt, phi[N];
static bitset<N> st;
static int n, a[N], m;
static int maxn;
static ll ans = 1;

auto init = [&] (int n)
{
    phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            phi[i] = i - 1;
            primes[++ cnt] = i;
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
};

auto Main = [&] ()
{
    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int t = read();
        a[t] ++;
        maxn = max(maxn, t);
    }

    while((1 << m) <= maxn) m ++;

    init(1 << m);
    dp[0] = 1;
    for(int i = 1; i <= (1 << m); i ++ )
    {
        for(int S = i; S; S = (S - 1) & i)
        {
            int T = i ^ S;
            if(T > S) break;
            dp[i] = (dp[i] + dp[T] * a[S]) % mod;
        }
    }

    for(int i = 1; i <= (1 << m); i ++ )
    {
        ans = (ans + phi[i + 1] * dp[i]) % mod;
    }

    for(int i = 0; i < a[0]; i ++ ) ans = ans * 2 % mod;

    cout << ans << endl;

    return 0;
};

Main();

    return 0;
}
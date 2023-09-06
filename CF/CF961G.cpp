#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

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

const int N = 1e6 + 10, mod = 1e9 + 7;
ll fact[N], invfact[N], mi[N];
ll k, n, sum;

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

int primes[N], cnt;
bitset<N> st;
inline void init(int nn)
{
    fact[0] = 1;
    for(int i = 1; i <= nn; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[nn] = qmi(fact[nn], mod - 2, mod);
    for(int i = nn - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;

    mi[1] = 1;
    for(int i = 2; i <= nn; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            mi[i] = qmi(i, n - 2, mod);
        }
        for(int j = 1; primes[j] <= nn / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            mi[t] = mi[primes[j]] * mi[i] % mod;
            if(i % primes[j] == 0) break;
        }
    }
}

ll ans;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) sum = (sum + read()) % mod;

    if(n == 1)
    {
        cout << sum << endl;
        return 0;
    }

    init(k);

    for(int i = 0; i < k; i ++ )
    {
        ans = (ans + ((i & 1) ? mod - 1 : 1) * invfact[i] % mod * invfact[k - 1 - i] % mod * (k - i + n - 1) % mod * mi[k - i] % mod) % mod;
    }

    cout << ans * sum % mod << endl;

    return 0;
}
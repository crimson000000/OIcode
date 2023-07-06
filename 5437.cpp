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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int mod = 998244353, N = 1e7 + 100;
ll n, k;
ll ans;

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

int primes[N << 1], cnt;
bool st[N << 1];
int f[N], s[N << 1];

void init(int n)
{
    s[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            s[i] = qmi(i, k, mod);
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            s[primes[j] * i] = (ll)s[primes[j]] * s[i] % mod;
            if(i % primes[j] == 0) break;
        }
    }
    for(int i = 1; i <= n; i ++ ) s[i] = ((ll)s[i - 1] + s[i]) % mod;
}

int pre[N], suf[N], invfact[N], nfact;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    init((k + 3) << 1);
    f[1] = 0;
    for(int i = 2; i <= k + 3; i ++ ) f[i] = ((ll)f[i - 1] + s[(i << 1) - 1] - s[i] + mod) % mod;

    nfact = pre[0] = pre[k + 4] = suf[k + 4] = suf[0] = 1;
    for(int i = 1; i <= k + 3; i ++ )
    {
        nfact = (ll)nfact * i % mod;
        pre[i] = (ll)pre[i - 1] * (n - i) % mod;
    }

    invfact[k + 3] = qmi(nfact, mod - 2, mod);
    for(int i = k + 3; i > 0; i -- )
        suf[i] = (ll)suf[i + 1] * (n - i) % mod;
    for(int i = k + 2; i >= 0; i -- )
        invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;

    ll ans = 0;
    for(int i = 1; i <= k + 3; i ++ )
    {
        int x = (ll)f[i] * pre[i - 1] % mod * (ll)suf[i + 1] % mod * (ll)invfact[i - 1] % mod * (ll)invfact[k + 3 - i] % mod;
        if((k + 3 - i) & 1) 
            x = mod - x;
        ans = (ans + x) % mod;
    }

    cout << (ll)ans * 2 % mod * qmi(n, mod - 2, mod) % mod << endl;

    return 0; 
}

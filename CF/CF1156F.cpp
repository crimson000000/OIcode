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

const int N = 5000 + 10, mod = 998244353;
ll a[N];
int f[N][N], s[N], g[N][N];
int fact[N];
int cnt[N];
int n;

ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll inv(ll a)
{
    return qmi(a, mod - 2, mod);
}


int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        cnt[a[i]] ++;
        fact[i] = (ll)fact[i - 1] * i % mod;
    }

    s[0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = n; j >= 0; j -- )
        {
            f[i][j] = ((ll)s[j - 1] * cnt[i] % mod);
            g[i][j + 1] = (ll)s[j - 1] * cnt[i] % mod * (cnt[i] - 1) % mod;
            s[j] = (s[j] + f[i][j]) % mod;
        }

    int ans = 0;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            ans = (ans + (ll)g[i][j] * fact[n - j] % mod) % mod;
    
    cout << (ll)ans * inv(fact[n]) % mod << endl;
    
    return 0;
}

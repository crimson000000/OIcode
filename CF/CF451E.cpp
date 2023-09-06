#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 50, mod = 1e9 + 7;
ll inv[N], a[N];
ll n, m;

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

ll C(ll n, ll m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    ll res = 1;
    for(ll i = n - m + 1; i <= n; i ++ )
        res = res * i % mod;
    for(int i = 1; i <= m; i ++ )
        res = res * inv[i] % mod;
    return res;
}

ll lucas(ll n, ll m)
{
    if(n < m) return 0;
    if(!m) return 1;
    return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> m;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    for(int i = 1; i <= 40; i ++ ) 
        inv[i] = qmi(i, mod - 2, mod);

    // for(int i = 0; i <= 10; i ++ )
    // {
    //     for(int j = 0; j <= i; j ++ )
    //         cout << lucas(i, j) << ' ';
    //     puts("");
    // }
    
    ll ans = 0;
    for(int i = 0; i < 1 << n; i ++ )
    {
        if(i == 0)
        {
            ans = (ans + lucas(n + m - 1, n - 1)) % mod;
            continue;
        }
        ll t = n + m;
        bool cnt = 0;
        for(int j = 1; j <= n; j ++ )
            if(i >> (j - 1) & 1)
            {
                t -= a[j] + 1;
                cnt ^= 1;
            }
        
        t --;
        
        if(cnt) ans = (ans - lucas(t, n - 1)) % mod;
        else ans = (ans + lucas(t, n - 1)) % mod;
    }

    cout << (ans % mod + mod) % mod << endl;
    
    return 0;
}

#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define ll __int128
typedef pair<int, int> PII;

inline __int128 read()
{
    __int128 x = 0, f = 1;
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

void write(__int128 x)
{
    if(!x) return;
    write(x / 10);
    putchar(x % 10 + '0');
}

ll n, ans;

inline ll mul(ll a, ll b, ll p) 
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

// solve ax + by = c
ll solve(ll a, ll b, ll c)
{
    ll x, y;
    ll d = exgcd(a, b, x, y);
    if(c % d != 0) return 1e30;
    ll mod = b / d;
    x = mul((c / d % mod + mod) % mod, (x % mod + mod) % mod, mod);

    return a * x;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    n <<= 1;
    ans = n - 1;

    for(ll i = 2; i <= n / i; i ++ )
    {
        if(n % i == 0)
        {
            ll a = i, b = n / i;
            ll c = b - 1;
            ans = min(ans, solve(a, b, c));

            a = n / i, b = i;
            c = b - 1;
            ans = min(ans, solve(a, b, c));
        }
    }

    write(ans);
    
    return 0;
}

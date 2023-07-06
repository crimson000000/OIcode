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

ll T, k;

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

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

ll equation(ll a, ll n, ll p)
{
    ll A = a, B = p, C = n;
    ll x, y;
    ll d = exgcd(A, B, x, y);
    if(C % d) return -114514;
    ll mod = B / d;
    x = x * C / d % mod;
    x = (x % mod + mod) % mod;
    return x;
}

unordered_map<ll, ll> h;
ll bsgs(ll a, ll n, ll p)
{
    n %= p;
    if(a % p == 0 && n)
    {
        return -114514;
    }
    h.clear();
    ll t = sqrt(p);

    for(int i = 0; i < t; i ++ ) h[n * qmi(a, i, p) % p] = i % p;

    for(int i = 0; i <= t; i ++ )
    {
        ll s = qmi(a, i * t, p) % p;
        if(h.find(s) != h.end())
        {
            return t * i - h[s];
        }
    }
    return -114514;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    T = read(), k = read();
    while(T -- )
    {
        ll y = read(), z = read(), p = read();
        if(k == 1)
        {
            printf("%lld\n", qmi(y, z, p));
        }
        else if(k == 2)
        {
            ll t = equation(y, z, p);
            if(t == -114514) puts("Orz, I cannot find x!");
            else printf("%lld\n", t);
        }
        else
        {
            ll t = bsgs(y, z, p);
            if(t == -114514) puts("Orz, I cannot find x!");
            else printf("%lld\n", t);
        }
    }
    
    return 0;
}

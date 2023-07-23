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

using i128 = __int128;

ll prm[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = (i128)res * a % p;
        a = (i128)a * a % p;
        k >>= 1;
    }
    return res;
}

mt19937 rnd(time(0));

inline bool miller(ll n)
{
    if(n < 3 || (n & 1) == 0) return n == 2;
    ll u = n - 1, t = 0;
    while(!(u & 1)) u >>= 1, t ++;
    for(int test = 1; test <= 8; test ++ )
    {
        ll a = rnd() % (n - 2) + 2, v = qmi(a, u, n);
        if(v == 1) continue;
        int s;
        for(s = 0; s < t; s ++ )
        {
            if(v == n - 1) break;
            v = (i128)v * v % n;
        }
        if(s == t) return false;
    }

    return true;
}

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

inline ll f(ll x, ll c, ll n)
{
    x %= n;
    return ((i128)x * x % n + c) % n;
}

ll maxf;
inline ll pollar(ll n)
{
    ll t = 0;
    ll c = rnd() % (n - 1) + 1;
    // for(int i = 0; i < 1145; i ++ ) t = f(t, c, n);
    ll s = t;
    ll step = 0, goal = 1;
    ll val = 1;
    for(goal = 1; ; goal <<= 1, s = t, val = 1)
    {
        for(step = 1; step <= goal; step ++ )
        {
            t = f(t, c, n);
            val = (i128)val * abs(t - s) % n;
            if(!val) return n;
            if(step % 127 == 0)
            {
                ll d = gcd(val, n);
                if(d > 1) return d;
            }
        }
        ll d = gcd(val, n);
        if(d > 1) return d;
    }
}

inline void solve(ll n)
{
    if(n <= maxf || n < 2) return;
    if(miller(n))
    {
        maxf = max(maxf, n);
        return;
    }
    ll p = n;
    while(p >= n) p = pollar(n);
    while(n % p == 0) n /= p;
    solve(n), solve(p);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        ll n = read();
        maxf = 0;
        solve(n);
        if(maxf == n)
            puts("Prime");
        else printf("%lld\n", maxf);
    }

    return 0;
}

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

ll p;
ll n, m, down;
ll sum;
ll ans = 1;
ll w[100];

namespace exlucas
{
    const int N = 10010;
    struct dividor
    {
        ll p, s;
    }d[N];
    ll a[N], b[N];
    ll dcnt;

    void init()
    {
        memset(d, 0, sizeof d);
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        dcnt = 0;
    }

    void divide(ll p)
    {
        for(ll i = 2; i <= p / i; i ++ )
        {
            if(p % i == 0)
            {
                d[++ dcnt].p = i;
                d[dcnt].s = 1;
                while(p % i == 0)
                {
                    p /= i;
                    d[dcnt].s *= i;
                }
            }
        }
        if(p > 1) d[++ dcnt] = {p, p};
    }

    ll qmi(ll a, ll k, ll p)
    {
        ll res = 1;
        while(k)
        {
            if(k & 1) res = (__int128)res * a % p;
            a = a * a % p;
            k >>= 1;
        }
        return res;
    }

    ll f(ll n, ll p, ll pk)
    {
        if(n == 0) return 1;
        ll res = 1;
        for(ll i = 1; i <= pk; i ++ )
        {
            if(i % p)
            {
                res = res * i % pk;
            }
        }
        res = qmi(res, n / pk, pk);
        for(int i = pk * (n / pk); i <= n; i ++ )
        {
            if(i % p)
                res = res * (i % pk) % pk;
        }
        return f(n / p, p, pk) * res % pk;
    }

    ll g(ll n, ll p)
    {
        if(n < p) return 0;
        return n / p + g(n / p, p);
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

    ll inv(ll a, ll p)
    {
        ll x, y;
        exgcd(a, p, x, y);
        return (x % p + p) % p;
    }

    ll crt(ll p)
    {
        ll ans = 0;
        for(int i = 1; i <= dcnt; i ++ )
        {
            ll M = p / b[i], T = inv(M, b[i]);
            ans = (ans + a[i] * M % p * T % p) % p;
        }
        return ans;
    }

    ll get(ll n, ll m, ll p)
    {
        divide(p);
        for(int i = 1; i <= dcnt; i ++ )
        {
            ll pi = d[i].p, pki = d[i].s;
            b[i] = pki;
            a[i] = f(n, pi, pki) * inv(f(m, pi, pki), pki) % pki * inv(f(n - m, pi, pki), pki) % pki
                    * qmi(pi, g(n, pi) - g(m, pi) - g(n - m, pi), pki) % pki;
        }
        return crt(p);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    p = read();
    n = read(), m = read();
    down = n;

    for(int i = 1; i <= m; i ++ )
    {
        w[i] = read();
        sum += w[i];
    }

    if(sum > n) puts("Impossible");
    else
    {
        for(int i = 1; i <= m; i ++ )
        {
            exlucas::init();
            ans = ans * exlucas::get(down, w[i], p) % p;
            down -= w[i];
        }
        cout << ans << endl;
    }
    
    return 0;
}

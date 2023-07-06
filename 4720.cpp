#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
typedef long long ll;
#define int ll


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

inline void write(__int128 x)
{
    if(x == 0) return;
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x > 9)  
        write(x / 10);
    putchar('0' + x % 10);
}

ll n, m, p;

namespace exlucas
{
    const int N = 10010;
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    struct dividor
    {
        ll p, s;
    }d[N];
    ll a[N], b[N];
    int dcnt;

    void init()
    {
        dcnt = 0;
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        memset(d, 0, sizeof d);
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
        if(p != 1) d[++ dcnt] = {p, p};
    }

    ll qmi(ll a, ll k, ll p)
    {
        a %= p;
        ll res = 1;
        while(k)
        {
            if(k & 1) res = (__int128)res * a % p;
            a = (__int128)a * a % p;
            k >>= 1; 
        }
        return res;
    }

    ll mul(ll a, ll b, ll p)
    {
        ll res = 0;
        a %= p, b %= p;
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
        ll d = exgcd(a, p, x, y);
        return (x % p + p) % p;
    }

    ll f(ll n, ll p, ll pk)
    {
        if(n == 0) return 1;
        ll res = 1;
        for(ll i = 1; i <= pk; i ++ )
        {
            if(i % p != 0)
            {
                res = (__int128)res * i % pk;
            }
        }
        res = qmi(res, (n / pk), pk);
        for(ll i = pk * (n / pk); i <= n; i ++ )
        {
            if(i % p != 0)
            {
                res = (__int128)res * (i % pk) % pk;
            }
        }
        return res * f(n / p, p, pk) % pk;;
    }

    ll g(ll n, ll p)
    {
        if(n < p) return 0;
        return (n / p) + g(n / p, p);
    }

    ll gcd(ll a, ll b)
    {
        if(!b) return a;
        return gcd(b, a % b);
    }

    ll lcm(ll a, ll b)
    {
        return a / gcd(a, b) * b;
    }

    ll excrt()
    {
        ll X = a[1], M = b[1];
        for(int i = 2; i <= dcnt; i ++ )
        {
            ll t, k;
            ll A = M, B = b[i], C = ((a[i] % B - X % B) % B + B) % B;
            ll d = exgcd(A, B, t, k);
            ll mod = B / d;
            t = (__int128)t * C / d % mod;
            X = X + t * M;
            M = lcm(M, b[i]);
        }
        return (X % M + M) % M;
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

        // for(int i = 1; i <= dcnt; i ++ ) printf("[%d %d]\n", d[i].p, d[i].s);
        for(int i = 1; i <= dcnt; i ++ )
        {
            ll pi = d[i].p, pki = d[i].s;
            b[i] = pki;
            
            a[i] = f(n, pi, pki) * inv(f(m, pi, pki), b[i]) % b[i] * inv(f(n - m, pi, pki), b[i]) % b[i]
                    * qmi(pi, g(n, pi) - g(m, pi) - g(n - m, pi), b[i]) % b[i];
        }
        return crt(p);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), p = read();
    cout << exlucas::get(n, m, p) << endl;
    
    return 0;
}

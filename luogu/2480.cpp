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

const ll mod = 999911659, mod1 = mod - 1;
ll q, n;
ll fact[1000010];

void init(ll p)
{
    fact[0] = 1;
    for(int i = 1; i <= p; i ++ )
        fact[i] = fact[i - 1] * i % p;
}

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

// 2 3 4679 35617

void divide(ll a)
{
    for(ll i = 2; i <= a / i; i ++ )
    {
        while(a % i == 0)
        {
            cout << i << ' ';
            a /= i;
        }
    }
    if(a) cout << a << endl;
}

inline ll inv(ll a, ll p)
{
    return qmi(a, p - 2, p);
}

ll C(ll n, ll m, ll p)
{
    if(n < m) return 0;
    return fact[n] * inv(fact[m], p) % p * inv(fact[n - m], p) % p;
}

ll lucas(ll n, ll m, ll p)
{
    if(n < m) return 0;
    if(!m) return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
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

ll gcd(ll a, ll b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

ll b[10], a[10];
ll CRT()
{
    ll X = a[1], M = b[1];
    for(int i = 2; i <= 4; i ++ )
    {
        ll t, k;
        ll A = M, B = b[i], C = (a[i] - X % B + B) % B;
        ll d = exgcd(A, B, t, k);
        ll md = B / d; 
        t = t * C / d % md;
        X = X + t * M;
        M = lcm(M, b[i]);
        X = (X % M + M) % M;
    }

    return X;
}

void calc()
{
    for(int k = 1; k <= 4; k ++ )
    {
        init(b[k]);
        for(ll i = 1; i <= n / i; i ++ )
        {
            if(n % i == 0)
            {
                a[k] = (a[k] + lucas(n, i, b[k])) % b[k];
                if(i * i != n) a[k] = (a[k] + lucas(n, n / i, b[k])) % b[k];
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> q;
    if(q % mod == 0) 
    {
        cout << 0 << endl;
        return 0;
    }

    b[1] = 2, b[2] = 3, b[3] = 4679, b[4] = 35617;
    calc();

    cout << qmi(q, CRT(), mod) << endl;
    
    return 0;
}

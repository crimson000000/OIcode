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

const int N = 1e4 + 10, M = 1e7 + 10;
const ll INF = 1e9;
ll k[N], r[N], g[N];
ll x[N], q[N];
ll maxx;
int n;

inline ll qmi(ll a, ll k, ll p)
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

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

inline ll exgcd(ll a, ll b, ll &x, ll &y)
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

inline ll Inv(ll a, ll p)
{
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

map<ll, int> mp;
inline ll bsgs(ll a, ll b, ll p)
{
    mp.clear();
    a %= p, b %= p;
    ll t = ceil(sqrt(p));

    ll A = 1;
    for(int i = 0; i < t; i ++, A = A * a % p)
        mp[b * A % p] = i;
    
    ll k = qmi(a, t, p);
    A = k;
    for(int i = 1; i <= t; i ++, A = A * k % p)
    {
        if(mp.count(A) && i * t - mp[A] >= 0)
        {
            return i * t - mp[A];
        }
    }
    return -1;
}

inline PII exbsgs(ll a, ll b, ll p)
{
    ll k = 0, na = 1 % p, d = 1;
    while(1)
    {
        ll nd = gcd(na * a % p, p);
        if(d == nd) break;
        if(na == b) return {k, -1};
        k ++;
        na = na * a % p;
        d = nd;
    }
    if(b % d) return {-1, -1};
    p /= d, na /= d, b /= d;
    b = b * Inv(na, p) % p;
    ll x = bsgs(a, b, p);
    if(x == -1) return {-1, -1};
    ll y = bsgs(a, 1 % p, p);
    return {x % y + k, y};
}

inline void Fail()
{
    puts("Impossible");
    exit(0);
}

inline bool merge(ll &a1, ll &m1, ll a2, ll m2)
{
    ll k1, k2;
    ll d = exgcd(m1, m2, k1, k2);
    ll C = ((a2 - a1) % m2 + m2) % m2;
    if(C % d) return false;
    k1 = (k1 % m2 + m2) % m2;
    a1 = (a1 + k1 * C / d % m2 * m1 % (m2 / d * m1));
    m1 = m1 * m2 / d;
    a1 %= m1;
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    ll X = -1;
    for(int i = 1; i <= n; i ++ )
    {
        k[i] = read();
        g[i] = read();
        r[i] = read();
        auto ans = exbsgs(k[i] % g[i], r[i] % g[i], g[i]);
        x[i] = ans.first, q[i] = ans.second;
        // cout << x[i] << ' ' << q[i] << endl;
        if(x[i] == -1) Fail();
        if(q[i] == -1) X = x[i];
        maxx = max(maxx, x[i]);
    }

    if(X != -1)
    {
        for(int i = 1; i <= n; i ++ )
            if(qmi(k[i], X, g[i]) != r[i])
                Fail();
        cout << X << endl;
        return 0;
    }

    ll P = 0, Q = 1;
    for(int i = 1; i <= n; i ++ )
    {
        if(Q > INF && (P - x[i]) % q[i]) Fail();
        if(Q <= INF && !merge(P, Q, x[i] % q[i], q[i])) Fail();
    }

    if(P < maxx) P += ((maxx - P - 1) / Q + 1) * Q;
    if(P > INF) Fail();
    cout << P << endl;
    
    return 0;
}

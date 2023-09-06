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
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 110, mod = 1e9 + 7;
const int M = 10010;
ll a[N], b[N];
int n, m;

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

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

struct node
{
    ll k, b;
    node() {k = b = 0; }
    node(ll _k, ll _b): k(_k), b(_b) {};
}f[M], g[M];

struct func
{
    ll a, b, c;
    func() {a = b = c = 0; }
    func(ll _a, ll _b, ll _c): a(_a), b(_b), c(_c) {};
};

ll P[M];
inline void divide(ll x)
{
    for(int i = 2; i <= x / i; i ++ )
    {
        if(x % i == 0)
        {
            P[++ m] = i;
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) P[++ m] = x;
}

bool vis;
inline bool solve(ll b, ll k)
{
    for(int i = 1; i <= m; i ++ ) g[i] = node(0, 0);
    for(int i = 1; i <= m; i ++ )
    {
        while(k % P[i] == 0) k /= P[i], g[i].k ++;
        while(b % P[i] == 0) b /= P[i], g[i].b ++;
    }
    if(!vis)
    {
        vis = true;
        for(int i = 1; i <= m; i ++ ) f[i] = g[i];
        return true;
    }

    for(int t = 0; t < 3; t ++ )
        for(int i = 1; i <= m; i ++ )
        {
            ll fb = f[i].b;
            ll fk = f[i].k;
            ll gk = g[i].k;
            ll gb = g[i].b;
            if(!fk && !gk)
            {
                if(fb != gb) return false;
            }
            else if(!fk || !gk)
            {
                int tg = 0;
                if(!fk) swap(fk, gk), swap(fb, gb), tg = 1;
                if(gb < fb || (gb - fb) % fk) return false;
                ll k = (gb - fb) / fk;
                if(tg)
                    for(int j = 1; j <= m; j ++ )
                        g[j].b += g[j].k * k, g[j].k = 0;
                else
                    for(int j = 1; j <= m; j ++ )
                        f[j].b += f[j].k * k, f[j].k = 0;
            }
        }

    func F;
    int flag = 0;
    ll X = -1, Y = -1;
    for(int i = 1; i <= m; i ++ )
    {
        ll fb = f[i].b;
        ll fk = f[i].k;
        ll gk = g[i].k;
        ll gb = g[i].b;
        if(fk && gk)
        {
            if(!flag) F = func(fk, -gk, gb - fb), flag = 1;
            else if(flag == 1)
            {
                ll A = fk, B = -gk, C = gb - fb;
                ll d = gcd(F.a, A);
                ll g1 = A / d, g2 = F.a / d;
                F.a *= g1, F.b *= g1, F.c *= g1;
                A *= g2, B *= g2, C *= g2;
                if(A == F.a && B == F.b)
                {
                    if(F.c != C) return false;
                    else
                    {
                        ll D = gcd(F.a, gcd(abs(F.b), abs(F.c)));
                        F.a /= D, F.b /= D, F.c /= D;
                        continue;
                    }
                }
                else
                {
                    C -= F.c, B -= F.b;
                    if(C < 0) C *= -1, B *= -1;
                    if(B < 0 || C % B) return false;
                    Y = C / B;
                    X = (F.c - F.b * Y) / F.a;
                    if(X < 0 || (F.c - F.b * Y) % F.a) return false;
                    flag = 2;
                }
            }
            else if(flag == 2)
            {
                ll A = fk, B = -gk, C = gb - fb;
                if(A * X + B * Y != C) return false;
            }
        }
    }

    if(flag == 2)
    {
        for(int i = 1; i <= m; i ++ )
            f[i].b += f[i].k * X, f[i].k = 0;
    }
    if(flag == 1)
    {
        ll x, y;
        ll d = exgcd(F.a, -F.b, x, y);
        y = -y;
        // cout << x << ' ' << y << endl;
        if(F.c % d) return false;
        ll kx = -F.b / d;
        ll ky = F.a / d;
        x *= F.c / d;
        y *= F.c / d;
        ll tx = 0, ty = 0;
        if(x < 0) tx = -((-x + kx - 1) / kx);
        else tx = x / kx;
        if(y < 0) ty = -((-y + ky - 1) / ky);
        else ty = y / ky;
        x -= kx * min(tx, ty);
        y -= ky * min(tx, ty);
        for(int i = 1; i <= m; i ++ )
            f[i].b += f[i].k * x, f[i].k *= kx;
    }
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read(), b[i] = read();
        divide(a[i]);
        divide(b[i]);
    }

    sort(P + 1, P + m + 1);
    m = unique(P + 1, P + m + 1) - P - 1;

    for(int i = 1; i <= n; i ++ )
        if(!solve(a[i], b[i]))
        {
            puts("-1");
            return 0;
        }

    ll res = 1;
    for(int i = 1; i <= m; i ++ )
        res = res * qmi(P[i], f[i].b, mod) % mod;
    
    cout << res << endl;

    return 0;
}

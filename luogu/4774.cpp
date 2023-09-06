#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
#define ll __int128
#define int __int128

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

void write(__int128 a)
{
    if(!a) return;
    if(a < 0)
    {
        putchar('-');
        a = -a;
    }
    write(a / 10);
    putchar(a % 10 + '0');
}

const int N = 1e6 + 10;
ll a[N], atk[N], p[N], sword[N], have[N];
ll n, m;
multiset<ll> s;

// now there is the set but I dont know how to use multiset555
/*struct node
{
    int l, r;
    ll val; 
    int key, siz;
}t[N];
int root, cnt;

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline int New(ll val)
{
    t[++ cnt].val = val;
    t[cnt].key = rand();
    t[cnt].siz = 1;
    return cnt;
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void split(int p, ll val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[p].val <= val)
        {
            x = p;
            split(t[p].r, val, t[p].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, val, x, t[p].l);
        }
        pushup(p);
    }
}

int x, y, z;
inline void insert(ll val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

inline ll getpre(ll val)
{
    split(root, val - 1, x, y);
    int p = x;
    while(t[p].r) p = t[p].r;
    ll ret = t[p].val;
    root = merge(x, y);
    return ret;
}

inline ll getnxt(ll val)
{
    split(root, val, x, y);
    int p = y;
    while(t[p].l) p = t[p].l;
    ll ret = t[p].val;
    root = merge(x, y);
    return ret;
}

void del(int val)
{
    split(root, val - 1, x, y);
    split(y, val, y, z);
    y = merge(t[y].l, t[y].r);
    root = merge(merge(x, y), z);
}
// ok now the set is over555
*/

// begin with math /kk
ll gcd(ll a, ll b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

// fxxk exgcd
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

ll b[N], maxn = 0;
// Chinese Residual theorem = grandson theorem -by malongze
inline void equation_set()
{
    for(int i = 1; i <= m; i ++ ) s.insert(have[i]);
    
    for(int i = 1; i <= n; i ++ )
    {
        auto u = s.upper_bound(a[i]);
        if(u != s.begin()) u --;

        b[i] = *u;

        s.insert(sword[i]);
        s.erase(u);
        
        maxn = max(maxn, (a[i] - 1) / b[i] + 1);
    }
}

ll mul(ll a, ll b, ll p)
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

// excrt -> nausea crt
ll excrt()
{
    ll M = 1, X = 0;
    for(int i = 1; i <= n; i ++ )
    {
        ll A = mul(M, b[i], p[i]);
        ll B = p[i];
        ll C = ((a[i] - X * b[i] % p[i]) % p[i] + p[i]) % p[i];
        ll t, k;
        ll d = exgcd(A, B, t, k);
        if(C % d != 0) return -1;

        ll mod = B / d;
        t = (t % p[i] + p[i]) % p[i];
        t = mul(t, C / d, mod);
        ll MM = M * p[i] / d;
        X = (X + mul(t, M, MM)) % MM;
        M = MM;
        X = (X % M + M) % M;
    }
    if(X < maxn) X += ((maxn - X - 1) / M + 1) * M;
    return X;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ll T = read();
    
    while(T -- )
    {
        s.clear();
        n = read(), m = read();
        maxn = 0;

        for(int i = 1; i <= n; i ++ ) a[i] = read();
        for(int i = 1; i <= n; i ++ ) p[i] = read();
        for(int i = 1; i <= n; i ++ ) sword[i] = read();
        for(int i = 1; i <= m; i ++ ) have[i] = read();

        equation_set();

        // if(T == 4)
        // {
        //     for(int i = 1; i <= n; i ++ ) printf("%lld %lld %lld\n", b[i], a[i], p[i]);
        // }

        ll t = excrt();
        write(t);
        puts("");
    }
    
    return 0;
}

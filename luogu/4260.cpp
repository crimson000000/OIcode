#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

namespace IO
{
    const int S = 1 << 20;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    inline int read(int &p)
    {
        static int c, q;
        p = 0/*, q = 1; */;
        while ((c = gc()) < '0' || c > '9')
            /* (c == '-') && (q = -1) */;
        p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            p = p * 10 + (c ^ '0');
        return p/*  *= q */;
    }
    inline void write(int x)
    {
        (x < 0) && (putchar('-'), x = -x);
        (x > 9) && (write(x / 10), true);
        putchar(x % 10 + '0');
    }
}
using IO::read;
using IO::write;

const int N = 2.5e5 + 10, mod = 1e9 + 7;
ll fact[N], invfact[N];
int Q;

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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
} 

int pos[N];
int x[N], y[N];

struct query
{
    int id;
    int l, r;
    
    bool operator < (const query& a) const
    {
        if(pos[l] != pos[a.l]) return pos[l] < pos[a.l];
        return pos[r] < pos[a.r];
    }
}q[N]; 
ll ans[N];

ll now = 2;
int L = 1, R = 1;
int maxn = 0;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 5);

    read(Q);
    int useless;
    read(useless);

    for(int i = 1; i <= Q; i ++ )
    {
        int n, m;
        read(n), read(m);
        x[i] = n, y[i] = m;
        maxn = max(maxn, n + m);
        q[i] = {i, n + m, min(n, m) - 1};
        if(n >= m) ans[i] = (n - m) * C(n + m, n) % mod;
    }
    
    int _ = pow(maxn, 0.48);
    for(int i = 1; i <= maxn; i ++ )
        pos[i] = (i - 1) / _ + 1;

    sort(q + 1, q + Q + 1);
    for(int i = 1; i <= Q; i ++ )
    {
        while(L > q[i].l) {L --; now = (now + C(L, R)) % mod * invfact[2] % mod;}
        while(R < q[i].r) {now = (now + C(L, R + 1)) % mod; R ++ ;}
        while(L < q[i].l) {now = (now * 2 % mod - C(L, R) + mod) % mod; L ++;}
        while(R > q[i].r) {now = (now - C(L, R) + mod) % mod; R -- ;};
        ans[q[i].id] = (ans[q[i].id] + now) % mod;
    }

    for(int i = 1; i <= Q; i ++ )
    {
        write(ans[i] * qmi(C(x[i] + y[i], x[i]), mod - 2, mod) % mod);
        putchar('\n');
    }

    return 0;
}
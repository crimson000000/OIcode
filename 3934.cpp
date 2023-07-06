#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int long long

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

const int N = 1e6 + 10, M = 2e7 + 10;
int phi[M], primes[M], cnt;
bool st[M];

void init(int n)
{
    phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0)
            {
                phi[primes[j] * i] = primes[j] * phi[i];
                break;
            }
            phi[primes[j] * i] = (primes[j] - 1) * phi[i];
        }
    }
}

int n, m;
int a[N];

struct treearray
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    inline void change(int l, int r, int val)
    {
        add(l, val), add(r + 1, -val);
    }
}t;

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1, tagx = 0, tag = 0;
    if(a >= p)
    {
        a %= p;
        tagx = true;
    }
    while(k)
    {
        if(k & 1)
        {
            res = res * a;
            tag |= tagx;
            if(res >= p) res %= p, tag = true;
        }
        if(a >= p) tagx = true, a %= p;
        a = a * a;
        if(a >= p) tagx = true, a %= p;
        k >>= 1;
    }
    if(tag) return res + p;
    else return res;
}

ll solve(int l, int r, int p)
{
    if(p == 1) return 1;
    if(l > r) return 1;
    int cur = t.query(l) + a[l], y = solve(l + 1, r, phi[p]);
    return qmi(cur, y, p);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(M - 5);
    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
    }

    while(m -- )
    {
        int op = read(), x = read(), y = read(), p = read();
        if(op == 1)
        {
            t.change(x, y, p);
        }
        else
        {
            cout << solve(x, y, p) % p << endl;
        }
    }
    
    return 0;
}
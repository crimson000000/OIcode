#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

const int N = 1e6 + 10;
struct node
{
    int l, r;
    mutable ll v;

    bool operator < (const node& N) const
    {
        return l < N.l;
    }
};

int n, m, seed, vmax;

set<node> t;

auto split(int x)
{
    auto it = t.lower_bound((node){x, 0, 0});
    if(it -> l == x && it != t.end()) return it;
    it --;
    int l = it -> l, r = it -> r, v = it -> v;
    t.erase(it);
    t.insert((node){l, x - 1, v});
    return t.insert((node){x, r, v}).first;
}

void assign(int l, int r, ll val)
{
    auto itr = split(r + 1), itl = split(l);
    t.erase(itl, itr);
    t.insert((node){l, r, val});
}

void add(int l, int r, ll v)
{
    auto itr = split(r + 1), itl = split(l);
    for(; itl != itr; ++ itl)
    {
        itl -> v += v;
    }
}

vector<pair<ll, int> > aa;
int kth(int l, int r, ll k)
{
    auto itr = split(r + 1), itl = split(l);
    aa.clear();
    for(; itl != itr; ++ itl) aa.push_back({itl -> v, (itl -> r - itl -> l + 1)});
    sort(aa.begin(), aa.end());
    for(auto u : aa)
    {
        k -= u.second;
        if(k <= 0) return u.first;
    }
}

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    a %= p;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

ll calc(int l, int r, ll k, ll p)
{
    auto itr = split(r + 1), itl = split(l);
    ll res = 0;
    for(; itl != itr; ++ itl )
    {
        ll a = itl -> v;
        ll s = itl -> r - itl -> l + 1;
        res = (res + qmi(a, k, p) * (ll)s % p) % p;
    }
    return res;
}

ll rnd()
{
    ll ret = seed;
    seed = ((ll)seed * 7 + 13) % 1000000007;
    return ret;
}

int a[N];

void print()
{
    for(auto it = t.begin(); it != t.end(); ++ it)
    {
        for(int i = 1; i <= it -> r - it -> l + 1; i ++ )
            cout << it -> v << ' ';
    }
    puts("");
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%lld%lld%lld%lld", &n, &m, &seed, &vmax);

    for(int i = 1; i <= n; i ++ )
    {
        a[i] = (rnd() % vmax) + 1;
        t.insert((node){i, i, a[i]});
    }

    t.insert((node){n + 10, n + 10, 0});

    while(m -- )
    {
        
        int op = rnd() % 4 + 1;
        int l = rnd() % n + 1, r = rnd() % n + 1;
        if(l > r) swap(l, r);
        
        if(op == 1)
        {
            ll x = rnd() % vmax + 1;
            add(l, r, x);
        }
        else if(op == 2)
        {
            ll x = rnd() % vmax + 1;
            assign(l, r, x);
        }
        else if(op == 3)
        {
            ll x = rnd() % (r - l + 1) + 1;
            cout << kth(l, r, x) << endl;
        }
        else
        {
            ll x = (rnd() % vmax) + 1, y = rnd() % vmax + 1;
            cout << calc(l, r, x, y) << endl;
        }
    }
    
    return 0;
}

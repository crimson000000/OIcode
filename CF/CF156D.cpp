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

const int N = 1e6 + 10;
ll n, m, k, mod;
int siz[N];
int p[N];
vector<int> tt;

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

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

inline void merge(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return;
    if(siz[x] < siz[y]) swap(x, y);
    p[y] = x;
    siz[x] += siz[y];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), mod = read();

    for(int i = 1; i <= n; i ++ ) p[i] = i, siz[i] = 1;

    for(int i = 1; i <= m; i ++ ) 
    {
        int a = read(), b = read();
        merge(a, b);
    }

    for(int i = 1; i <= n; i ++ ) 
        if(find(i) == i)
        {
            k ++;
            tt.emplace_back(siz[i]);
        }
    
    if(k == 1) printf("%d\n", 1 % mod);
    else
    {
        ll ans = qmi(n, k - 2, mod);
        for(auto a : tt)
            ans = ans * a % mod;
        printf("%lld\n", ans % mod);
    }
    
    return 0;
}

#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
ll v[N];
int n;
bitset<N> mark;
int primes[N], cnt;
ll f[N];
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
map<ll, int> mp;

bitset<N> st;
void init(int n)
{
    f[1] = 0;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            f[i] = rnd();
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            f[t] = f[i] ^ f[primes[j]];
            if(i % primes[j] == 0) break;
        }
    }

    for(int i = 2; i <= n; i ++ ) f[i] ^= f[i - 1];
}

void out(int x)
{
    printf("%d\n", x);
    for(int i = 1; i <= n; i ++ )
        if(!mark[i]) printf("%d ", i);
    exit(0);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(n);

    ll all = 0;
    for(int i = 1; i <= n; i ++ ) all ^= f[i];

    if(!all) out(n);
    for(int i = 1; i <= n; i ++ )
    {
        if((all ^ f[i]) == 0)
        {
            mark[i] = true;
            out(n - 1);
        }
    }

    for(int i = 1; i <= n; i ++ ) mp[f[i]] = i;
    for(int i = 1; i <= n; i ++ )
        if(mp.count(all ^ f[i]))
        {
            mark[i] = true;
            mark[mp[all ^ f[i]]] = true;
            out(n - 2);
        }
    
    mark[2] = true;
    mark[(n - 1) / 2] = true;
    mark[n] = true;
    out(n - 3);

    return 0;
}
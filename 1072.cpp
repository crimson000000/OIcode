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

const int N = 1e5 + 10;
int primes[N], cnt;
bool st[N];

struct factor
{
    ll p, s;
}f[N];
int fcnt;
ll dividor[N];
int dcnt;

ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i]) primes[cnt ++ ] = i;
        for(int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

void dfs(int u, ll num)
{
    if(u == fcnt)
    {
        dividor[dcnt ++ ] = num;
        return;
    }

    for(int i = 0; i <= f[u].s; i ++ )
    {
        if(i) num *= f[u].p;
        dfs(u + 1, num);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ll T = read();

    init(N - 1);
    while(T -- )
    {
        ll a = read(), b = read(), c = read(), d = read();
        fcnt = dcnt = 0;
        
        ll t = d;
        for(int i = 0; primes[i] <= d / primes[i]; i ++ )
        {
            ll p = primes[i];
            if(t % p == 0)
            {
                ll s = 0;
                while(t % p == 0) t /= p, s ++ ;
                f[fcnt ++ ] = {p, s};
            }
        }
        if(t > 1) f[fcnt ++ ] = {t, 1};

        dfs(0, 1);
        ll s = 0;
        for(int i = 0; i < dcnt; i ++ )
        {
            ll x = dividor[i];
            if(gcd(x, a) == b && lcm(x, c) == d)
                s ++;
        }

        cout << s << endl;
    }
    
    return 0;
}

#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
using ll = long long;
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

const int N = 1e6 + 10, P = 131;
const int M = 1e7 + 10;
int n, k;
int a[N];
int cnt[N];
ull ppow[M];

int primes[M], pcnt;
bitset<M> st;
int mind[M];
int mp[M];

ull now;
unordered_map<ull, ll> cntt;
ll ans;

inline void init(int n)
{
    mind[1] = 0;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[pcnt] = i;
            mp[i] = pcnt ++;
            mind[i] = i;
        }
        for(int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            mind[primes[j] * i] = min(primes[j], mind[i]);
            if(i % primes[j] == 0) break;
        }
    }

    // for(int i = 1; i <= 100; i ++ ) cout << mind[i] << ' ';
}

inline void divide(int x)
{
    while(x != 1)
    {
        int dmin = mind[x];
        int s = 0;
        while(x % dmin == 0) s ++, x /= dmin;
        now = (now + ppow[mp[dmin]] * s);
        cnt[dmin] += s;
        while(cnt[dmin] >= k)
        {
            cnt[dmin] -= k;
            now = (now - ppow[mp[dmin]] * k);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ppow[0] = 1;
    for(int i = 1; i <= M - 5; i ++ )
        ppow[i] = ppow[i - 1] * ull(P);

    init(M - 5);
    
    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    cntt[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        divide(a[i]);
        ans += cntt[now];
        cntt[now] ++;
    }

    cout << ans << endl;

    return 0;
} 

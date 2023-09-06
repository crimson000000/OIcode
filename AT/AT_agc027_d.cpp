#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1010 + 10, M = 1e6 + 1000;
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int primes[M], cnt;
ll A[N], B[N];
ll a[N][N];
bitset<M> st;
int n;

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

inline ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

inline void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    init(10000);

    for(int i = 1; i <= n; i ++ ) 
        A[i] = primes[(i & 1) ? i / 2 + 1 : n + n - i / 2 + 1];
    
    for(int i = 1; i <= n; i ++ )
        B[i] = primes[((i & 1) ? n - i / 2 : n + i / 2) + (n & 1)];

    A[0] = A[n + 1] = B[0] = B[n + 1] = 1;

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            if((i + j) & 1)
                printf("%lld ", A[(i + j) / 2] * A[(i + j) / 2 + 1] * 
                B[(n + i - j + (n & 1)) / 2] * B[(n + i - j + (n & 1)) / 2 + 1] + 1);
            else
                printf("%lld ", A[(i + j) / 2] * B[(n + i - j + (n & 1)) / 2]);
        }
        puts("");
    }

    return 0;
}

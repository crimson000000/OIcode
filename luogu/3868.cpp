#define LOCAL
#include <bits/stdc++.h>
using namespace std;
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
ll a[N], b[N], in[N], m[N];
int n;
ll M = 1, X = 1;

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

ll gcd(ll a, ll b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d", &n);

    for(int i = 1; i <= n; i ++ ) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; i ++ ) scanf("%lld", &b[i]);

    X = a[1], M = b[1];
    for(int i = 2; i <= n; i ++ )
    {
        ll t, k;
        ll a1 = M, b1 = b[i], c = a[i] - X;
        ll d = exgcd(a1, b1, t, k);

        ll mod = b1 / d;
        t = (t * (c / d) % mod + mod) % mod;
        X = X + t * M;
        M = lcm(M, b[i]);
    }

    cout << (X % M + M) % M << endl;

    return 0;
}

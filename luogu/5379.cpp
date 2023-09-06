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

const int N = 3e5 + 10;
int a[N], b[N];
int n, p;

inline bool check(int q)
{
    for(int i = 0; i < n; i ++ )
        if(a[i] != a[(i + q) % n])
            return false;
    return true;
}

inline void modify(int q)
{
    for(int i = 0; i < n; i ++ )
        b[i] = (a[(i + q) % n] - a[i] + p) % p;
    memcpy(a, b, sizeof a);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), p = read();
    for(int i = 0; i < n; i ++ ) a[i] = read() % p;

    int t = 1;
    while(n % (ll)(t * p) == 0) t *= p;
    
    if(!check(t))
    {
        puts("-1");
        return 0;
    }

    int ans = 0;
    n = t;
    while(n > 1)
    {
        t = n / p;
        while(!check(t))
            modify(t), ans += t;
        n = t;
    }

    if(a[0] != 0) ans ++;

    cout << ans << endl;

    return 0;
}
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

const int N = 2e6 + 10;
ll a[N], d[N], sum;
int n;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        sum += a[i];
    }

    for(int i = 1; i <= n; i ++ )
        d[i] = a[i % n + 1] - a[i];

    ll c = (ll)n * (n + 1) / 2;

    if(sum % c != 0) 
    {
        puts("NO");
        return 0;
    }

    ll M = sum / c;
    // for(int i = 1; i <= n; i ++ ) cout << d[i] << endl;

    for(int i = 1; i <= n; i ++ )
    {
        ll m = (M - d[i]) / n;
        if((M - d[i]) % n != 0 || m < 0) 
        {
            puts("NO");
            return 0;
        }
    }
    
    puts("YES");

    return 0;
}

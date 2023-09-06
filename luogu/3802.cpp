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

ll a[10];
ll s;
long double ans = 1;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    for(int i = 1; i <= 7; i ++ ) 
    {
        a[i] = read();
        s += a[i];
    }

    for(int i = 1; i <= 6; i ++ )
        ans *= 1.0 * a[i] / (s - i + 1) * i;
    
    printf("%.3Lf\n", ans * a[7] * 7.0);

    return 0;
}
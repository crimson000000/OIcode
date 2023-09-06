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

const int N = 4e6 + 10;
bitset<N> f;
int n;
ll a[N];
ll sum;

int main()
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

    f[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        f = f | (f << a[i]);
    }
    
    for(int i = (sum + 1) / 2; i <= sum; i ++ )
        if(f[i])
        {
            cout << i << endl;
            return 0;
        }
 
    return 0;
}
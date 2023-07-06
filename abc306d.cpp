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
ll f[N][2];
int n;
ll a[N];
bool poi[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        ll x = read(), y = read();
        poi[i] = x, a[i] = y;
    }

    for(int i = 1; i <= n; i ++ )
    {
        f[i][0] = max(f[i][0], f[i - 1][0]);
        f[i][1] = max(f[i][1], f[i - 1][1]);
        if(poi[i]) f[i][1] = max(f[i][1], f[i - 1][0] + a[i]);
        else       
        {
            f[i][0] = max(f[i][0], f[i - 1][1] + a[i]);
            f[i][0] = max(f[i][0], f[i - 1][0] + a[i]);
        }
    }

    printf("%lld\n", max(f[n][0], f[n][1]));

    return 0;
}
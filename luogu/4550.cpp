#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
using ld = long double;

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
ld f[N], g[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = n - 1; i >= 0; i -- )
    {
        f[i] = f[i + 1] + 1.0 * n / (n - i);
        g[i] = g[i + 1] + 2.0 * i / (n - i) * f[i] + 2 * f[i + 1] + 1.0 * n / (n - i);
    }

    printf("%.2Lf\n", (f[0] + g[0]) / 2);

    return 0;
}
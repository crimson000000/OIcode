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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 260, M = 1010;
int n, m;
int w[N], v[N];
double f[M];

inline bool check(double mid)
{
    for(int i = 1; i <= m; i ++ )
        f[i] = -1e20;
    
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = m; j >= 0; j -- )
        {
            int k = min(j + w[i], m);
            f[k] = max(f[k], f[j] + v[i] - mid * w[i]); 
        }
    }

    return f[m] >= 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        w[i] = read(), v[i] = read();

    double l = 0, r = 1e6;
    while(r - l > 1e-6)
    {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    printf("%d\n", int(1000 * l));

    return 0;
}
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

const int N = 2010;
const double eps = 1e-8;
double p[N], u[N];
double f[N][N];
int cnt[N][N];
int n, a, b;

inline bool check(double mid)
{
    memset(f, 0, sizeof f);
    memset(cnt, 0, sizeof cnt);
    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j <= a; j ++ )
        {
            f[i][j] = f[i - 1][j];
            cnt[i][j] = cnt[i - 1][j];
            if(j != 0 && f[i - 1][j - 1] + p[i] >= f[i][j])
            {
                f[i][j] = f[i - 1][j - 1] + p[i];
                cnt[i][j] = cnt[i - 1][j - 1];
            }
            if(f[i - 1][j] + u[i] - mid >= f[i][j])
            {
                f[i][j] = f[i - 1][j] + u[i] - mid;
                cnt[i][j] = cnt[i - 1][j] + 1;
            }
            if(j != 0 && f[i - 1][j - 1] + p[i] + u[i] - p[i] * u[i] - mid >= f[i][j])
            {
                f[i][j] = f[i - 1][j - 1] + p[i] + u[i] - p[i] * u[i] - mid;
                cnt[i][j] = cnt[i - 1][j - 1] + 1;
            }
        }
    return cnt[n][a] <= b;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), a = read(), b = read();
    for(int i = 1; i <= n; i ++ ) cin >> p[i];
    for(int i = 1; i <= n; i ++ ) cin >> u[i];

    double l = 0, r = 1;
    while(r - l > eps)
    {
        double mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid;
    }

    printf("%.5lf\n", f[n][a] + l * b);

    return 0;
}
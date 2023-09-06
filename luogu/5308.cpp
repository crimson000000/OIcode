#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 1e5 + 10;
const ld eps = 1e-11;
ld f[N], a[N], b[N];
int cnt[N];
int q[N], hh, tt;
int n, k;

inline ld X(int x)
{
    return 1.0 / (n - x);
}

inline ld Y(int x)
{
    return f[x] - 1.0 * x / (n - x);
}

inline ld slope(int a, int b)
{
    return (Y(a) - Y(b)) / (X(a) - X(b));
}

inline bool check(ld mid)
{
    hh = 0, tt = -1;
    q[++ tt] = 0;
    for(int i = 1; i <= n; i ++ )
    {
        while(hh < tt && slope(q[hh], q[hh + 1]) >= -1.0 * i) 
            hh ++;
        int j = q[hh];
        f[i] = Y(j) + i * X(j) - mid;
        cnt[i] = cnt[j] + 1;
        while(hh < tt && slope(q[tt], q[tt - 1]) <= slope(q[tt], i))
            tt --;
        q[++ tt] = i;
    }

    return cnt[n] >= k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    
    ld l = -1000000, r = 1000000;
    while(r - l > eps)
    {
        ld mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    check(l);

    printf("%.9Lf\n", f[n] + 1.0 * l * k);

    return 0;
}

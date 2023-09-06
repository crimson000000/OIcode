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
ll f[N];
ll sum[N], a[N], s[N];
int q[N], hh, tt = -1;
int n, L;

struct point
{
    ll x, y;
}p[N];

template <class T>
inline T sq(T a)
{
    return a * a;
}

inline double slope(int a, int b)
{
    return (p[b].y - p[a].y) * 1.0 / (p[b].x - p[a].x);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), L = read() + 1;
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        sum[i] = sum[i - 1] + a[i];
        s[i] = sum[i] + i;
    }

    q[++ tt] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        while(hh < tt && slope(q[hh], q[hh + 1]) < -2 * (L - s[i])) hh ++;
        f[i] = f[q[hh]] + sq(s[q[hh]]) + 2 * s[q[hh]] * (L - s[i]) + sq(s[i] - L);
        p[i] = {s[i], f[i] + sq(s[i])};
        while(hh < tt && slope(i, q[tt]) < slope(q[tt - 1], q[tt])) tt --;
        q[++ tt] = i;
    }

    cout << f[n] << endl;

    return 0;
}
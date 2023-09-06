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
const double eps = 1e-10;
struct vec
{
    double x, y;
    bool operator < (const vec& a) const
    {
        if(fabs(x - a.x) > eps) return x < a.x;
        return y < a.y;
    }

    vec operator + (const vec& a) const
    {
        return {x + a.x, y + a.y};
    }

    vec operator - (const vec& a) const
    {
        return {x - a.x, y - a.y};
    }
}q[N];
int n;
vec stk[N];
int tt;
double ans;

inline double dist(vec a, vec b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double cross(vec a, vec b)
{
    return a.x * b.y - a.y * b.x;
}

inline double side(vec a, vec b, vec c)
{
    vec A = b - a;
    vec B = c - b;
    return cross(A, B);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) scanf("%lf%lf", &q[i].x, &q[i].y);

    sort(q + 1, q + n + 1);

    if(n < 3)
    {
        puts("-1");
        return 0;
    }

    stk[tt] = q[1], stk[++ tt] = q[2];
    for(int i = 3; i <= n; i ++ )
    {
        while(tt && side(stk[tt - 1], stk[tt], q[i]) < 0) tt --;
        stk[++ tt] = q[i];
    }

    stk[++ tt] = q[n - 1];
    for(int i = n - 2; i >= 1; i -- )
    {
        while(tt && side(stk[tt - 1], stk[tt], q[i]) < 0) tt --;
        stk[++ tt] = q[i];
    }

    // for(int i = 1; i <= tt; i ++ )
    // {
    //     printf("(%lf, %lf)\n", stk[i].x, stk[i].y);
    // }

    for(int i = 1; i <= tt; i ++ )
    {
        ans += dist(stk[i - 1], stk[i]);
    }
    
    printf("%.2lf\n", ans);

    return 0;
}


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

const int N = 1e6 + 10, eps = 1e-10;
const double PI = acos(-1);
struct vec
{
    double x, y;
    bool operator < (const vec& a) const
    {
        if(fabs(x - a.x) > eps) return x < a.x;
        return y < a.y;
    }
    vec operator + (const vec& a) const {return {x + a.x, y + a.y};}
    vec operator - (const vec& a) const {return {x - a.x, y - a.y};}
}q[N], stk[N];
int tt, cnt;
int n;
double a, b, phi, r, l;

inline void add(double x, double y)
{
    q[++ cnt] = {x, y};
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

inline double dist(vec a, vec b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double solve()
{
    sort(q + 1, q + cnt + 1);
    stk[++ tt] = q[1];
    stk[++ tt] = q[2];
    for(int i = 3; i <= cnt; i ++ )
    {
        while(tt > 1 && side(stk[tt - 1], stk[tt], q[i]) < 0) tt --;
        stk[++ tt] = q[i];
    }
    stk[++ tt] = q[cnt - 1];
    for(int i = cnt - 2; i; i -- )
    {
        while(tt > 1 && side(stk[tt - 1], stk[tt], q[i]) < 0) tt --;
        stk[++ tt] = q[i];
    }

    double res = 0;
    for(int i = 2; i <= tt; i ++ )
        res += dist(stk[i - 1], stk[i]);
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%lf%lf%lf", &a, &b, &r);
    
    a -= 2 * r, b -= 2 * r;
    phi = atan(a / b);
    l = sqrt(a * a + b * b) / 2;

    for(int i = 1; i <= n; i ++ )
    {
        double x, y, theta;
        scanf("%lf%lf%lf", &x, &y, &theta);
        double dx = cos(theta + phi) * l;
        double dy = sin(theta + phi) * l;
        add(x + dx, y + dy);
        add(x - dx, y - dy);
        dx = cos(theta - phi) * l;
        dy = sin(theta - phi) * l;
        add(x + dx, y + dy);
        add(x - dx, y - dy);
    }
    
    printf("%.2lf\n", solve() + 2 * r * PI);

    return 0;
}
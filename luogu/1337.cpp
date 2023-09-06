#define LOCAL
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1010;
PDD q[N];
double w[N];
PDD cur, np;
double ans = 1e18, ansx, ansy;
int n;

double rand(double l, double r)
{
    return (double)rand() / RAND_MAX * (r - l) + l;
}

double calc(PDD a)
{
    double res = 0;
    for(int i = 0; i < n; i ++ )
    {
        double dx = a.x - q[i].x;
        double dy = a.y - q[i].y;
        res += sqrt(dx * dx + dy * dy) * w[i];
    }
    return res;
}

void simulate_anneal()
{
    for(double t = 10000; t > 1e-6; t *= 0.9997)
    {
        np = {rand(cur.x - t, cur.x + t), rand(cur.y - t, cur.y + t)};
        double b = calc(np);
        double dt = b - ans;
        if(dt < 0)
        {
            cur = np;
            ansx = cur.x;
            ansy = cur.y;
            ans = b;
        }
        if(exp(-dt / t) > rand(0, 1)) cur = np;
    }
}

void sa()
{
    simulate_anneal();simulate_anneal();simulate_anneal();simulate_anneal();
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;

    for(int i = 0; i < n; i ++ ) 
    {
        cin >> q[i].x >> q[i].y >> w[i];
        cur.x += q[i].x;
        cur.y += q[i].y;
    }

    cur.x /= n;
    cur.y /= n;
    ans = calc(cur);

    sa();

    printf("%.3f %.3f\n", ansx, ansy);

    return 0;
}

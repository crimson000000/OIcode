#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

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

const int N = 510;
double a[N][N];
int n, m, ans, cnt;

struct item
{
    double s[N];
    int cost;

    // double operator [] (int x)
    // {
    //     return s[x];
    // }

    bool operator < (const item& I) const
    {
        return cost < I.cost;
    }
}b[N];

bool insert(item p)
{
    for(int i = 1; i <= m; i ++ )
    {
        if(fabs(p.s[i]) < 1e-4) continue;
        if(fabs(a[i][i]) < 1e-4)
        {
            for(int j = 1; j <= m; j ++ )
                a[i][j] = p.s[j];
            return true;
        }

        double tmp = p.s[i] / a[i][i];
        for(int j = i; j <= m; j ++ )
            p.s[j] -= tmp * a[i][j];
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            scanf("%lf", &b[i].s[j]);
    
    for(int i = 1; i <= n; i ++ ) scanf("%d", &b[i].cost);

    sort(b + 1, b + 1 + n);
    for(int i = 1; i <= n; i ++ )
    {
        if(insert(b[i]))
            ans += b[i].cost, cnt ++;
    }

    printf("%d %d\n", cnt, ans);
    
    return 0;
}

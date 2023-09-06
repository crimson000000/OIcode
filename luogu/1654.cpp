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

double p;
double g, f, len;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%lf", &p);
        g = p * (g + 3 * f + 3 * len + 1) + (1 - p) * g;
        f = p * (f + 2 * len + 1);
        len = p * (len + 1);
    }

    printf("%.1lf\n", g);
    
    return 0;
}

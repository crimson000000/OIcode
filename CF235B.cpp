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

const int N = 1e6 + 10;
double f[N];
double len;
double p[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
        scanf("%lf", &p[i]);

    for(int i = 1; i <= n; i ++ )
    {
        f[i] = (f[i - 1] + 2 * len + 1) * p[i] + f[i - 1] * (1 - p[i]);
        len = (len + 1) * p[i];
    }

    printf("%.15lf\n", f[n]);
    
    return 0;
}

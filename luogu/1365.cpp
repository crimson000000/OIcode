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
int n;
char s[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] == 'o')
        {
            f[i] = f[i - 1] + 2 * len + 1;
            len += 1;
        }
        else if(s[i] == 'x')
        {
            f[i] = f[i - 1];
            len = 0;
        }
        else
        {
            f[i] = (f[i - 1] + 2 * len + 1) * 0.5 + f[i - 1] * 0.5;
            len += (1 - len) / 2;
        }
    }
    
    printf("%.4lf\n", f[n]);

    return 0;
}

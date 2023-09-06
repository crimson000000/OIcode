#define LOCAL
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 3010;

inline int read()
{
    int x = 0, f = 1;
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

int n;
int a[N];
int f[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
  
    

    int T = read();
    while(T -- )
    {
        n = read();
        for(register int i = 1; i <= n; i ++ ) a[i] = read();
        memset(f, 0, sizeof f);

        f[0] = 1;
        f[1] = 0;

        for(int i = 0; i <= n; i ++ )
        {
            if(i - a[i] - 1 >= 0)
                if(f[i - a[i] - 1])
                    f[i] = 1;
            if(f[i] && i + 1 + a[i + 1] <= n) f[i + 1 + a[i + 1]] = 1;
        }

        if(f[n]) puts("YES");
        else puts("NO");
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
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

int a[50];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        if(a[i] == 0)
        {
            if(i % 2 == 0) 
            {
                puts("YES");
                return 0;
            }
            break;
        }
    }

    for(int i = n; i >= 1; i -- )
    {
        if(a[i] == 0)
        {
            if((n - i + 1) % 2 == 0) 
            {
                puts("YES");
                return 0;
            }
            break;
        }
    }

    puts("NO");
    
    return 0;
}

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
int a[N];
int n, res;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        res ^= a[i];
    }

    if(res == 0)
    {
        puts("lose");
        return 0;
    }
    else
    {
        for(int i = 1; i <= n; i ++ )
        {
            int newai = res ^ a[i];
            if(a[i] > newai)
            {
                printf("%d %d\n", a[i] - newai, i);
                a[i] = newai;
                for(int i = 1; i <= n; i ++ ) cout << a[i] << ' ';

                return 0;
            }
        }
    }
    
    return 0;
}

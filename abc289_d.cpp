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

const int N = 1e5 + 10;
int a[N];
int f[N];
bool st[N];
int n, p, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    p = read();

    for(int i = 1; i <= p; i ++ )
    {
        int t = read();
        st[t] = true;
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    m = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = a[i]; j <= m; j ++ )
        {
            if(!st[j])
                f[j] = min(f[j], f[j - a[i]] + 1);
        }

    if(f[m] > 0x3f3f3f3f / 2) puts("No");
    else puts("Yes");
    
    return 0;
}

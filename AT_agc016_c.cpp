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

int n, m, h, w;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), h = read(), w = read();
    if(n % h == 0 && m % w == 0)
    {
        puts("No");
        return 0;
    }

    puts("Yes");
    int val = (h * w - 1) * 1000 + 1;
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
            if(i % h == 0 && j % w == 0) printf("%d ", -val);
            else printf("1000 ");
        puts("");
    }

    return 0;
}

#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

using ld = long double;

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

const int N = 1e6 + 10, mod = 10000;
int ne[N], a[N];
int n, m, k;
bitset<N> vis;

inline void kmp(int a[])
{
    ne[1] = 0;
    for(int i = 2, j = 0; i <= m; i ++ )
    {
        while(j && a[j + 1] != a[i]) j = ne[j];
        if(a[j + 1] == a[i]) j ++;
        ne[i] = j;
    }
    vis.reset();
    for(int i = m; i; i = ne[i]) vis[i] = true;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    n = read(), k = read();

    while(k -- )
    {
        m = read();
        for(int i = 1; i <= m; i ++ ) a[i] = read();

        kmp(a);

        ll a = n, ans = 0;
        for(int i = 1; i <= m; i ++, a = a * n % mod)
            if(vis[i])
                ans = (ans + a) % mod;
        
        printf("%04lld\n", ans);
    }

    return 0;
}

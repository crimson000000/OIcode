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
int a[N], f[N], g[N], c[N];
int n, ans;

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
        f[i] = 1, g[i] = i;
        if(a[i - 1] < a[i]) f[i] += f[i - 1], g[i] = g[i - 1];
    } 

    for(int i = 1; i <= n; i ++ )
    {
        if(i != n) ans = max(ans, f[i] + 1);
        else ans = max(ans, f[i]);

        int last = g[i];
        if(last - 2 != -1)
        {
            if(a[last] - a[last - 2] > 1) 
                ans = max(f[i] + f[last - 2] + 1, ans);
        }
    }

    cout << ans << endl;

    return 0;
}

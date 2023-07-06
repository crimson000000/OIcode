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

const int N = 1e6 + 10, mod = 80112002;
int h[N], e[N], ne[N], idx;
int f[N], din[N], dout[N];
int q[N], tt = -1, hh;
int n, m, ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    din[b] ++, dout[a] ++;;
}

void topsort()
{
    for(int i = 1; i <= n; i ++ )
        if(!din[i])
        {
            q[++ tt] = i;
            f[i] = 1;
        }

    while(hh <= tt)
    {
        int x = q[hh ++];

        for(int i = h[x]; i != -1; i = ne[i])
        {
            int j = e[i];
            f[j] = (f[x] + f[j]) % mod;
            din[j] --;
            if(!din[j]) q[++ tt] = j;
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();
    
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(b, a);
    }

    topsort();

    for(int i = 1; i <= n; i ++ )
        if(!dout[i])
            ans = (ans + f[i]) % mod;

    cout << ans << endl;
    
    return 0;
}

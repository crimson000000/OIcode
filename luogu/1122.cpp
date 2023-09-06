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
int h[N], e[N], ne[N], idx;
int f[N], v[N];
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dp(int u, int fa)
{
    f[u] = v[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dp(j, u);
        f[u] += f[j];
    }

    if(f[u] < 0) f[u] = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    
    n = read();
    for(int i = 1; i <= n; i ++ ) v[i] = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }

    dp(1, 0);

    int res = 0;
    for(int i = 1; i <= n; i ++ ) res = max(res, f[i]);

    if(res == 0)
    {
        res = -0x3f3f3f3f;
        for(int i = 1; i <= n; i ++ ) res = max(res, v[i]);
    }
    cout << res << endl;

    return 0;
}

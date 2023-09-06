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
int h[N], e[N], ne[N], idx;
bool st[N];
int a[N], f[N];
int n, m, k;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u)
{
    st[u] = true;
    f[u] ++;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(st[j]) continue;
        dfs(j);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    k = read(), n = read(), m = read();

    for(int i = 1; i <= k; i ++ )
        a[i] = read();

    while(m -- )
    {
        int a = read(), b = read();
        add(a, b);
    }

    for(int i = 1; i <= k; i ++ )
    {
        memset(st, 0, sizeof st);
        dfs(a[i]);
    }

    int ans = 0;
    for(int i = 1; i <= n; i ++ )
        if(f[i] == k)
            ans ++ ;
    
    cout << ans << endl;
    
    return 0;
}

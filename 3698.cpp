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

const int N = 1010;
int h[N], e[N], ne[N], idx;
int n, m, depth;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa, int dep)
{
    depth = max(depth, dep);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u, dep + 1);
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
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs(0, 0, 1);

    if(m < depth) cout << m + 1 << endl;
    else cout << min(n, depth + (m - depth + 1) / 2) << endl;
    
    return 0;
}

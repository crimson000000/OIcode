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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
vector<int> f[N >> 1];
int ans[N];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N], len[N], son[N];
void dfs1(int u, int f)
{
    fa[u] = f;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs1(j, u);
        if(len[j] >= len[son[u]])
        {
            son[u] = j;
            len[u] = len[j] + 1;
        }
    }
}

void dfs2(int u)
{
    if(!son[u])
    {
        f[u].push_back(1);
        ans[u] = 0;
        return;
    }
    dfs2(son[u]);
    swap(f[u], f[son[u]]);
    f[u].push_back(1);
    ans[u] = ans[son[u]];
    if(f[u][ans[u]] == 1) ans[u] = len[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u] || j == son[u]) continue;
        dfs2(j);
        for(int i = len[j]; i >= 0; i -- )
        {
            int tmp = i + len[u] - len[j] - 1;
            f[u][tmp] += f[j][i];
            if(f[u][tmp] > f[u][ans[u]] || (f[u][tmp] == f[u][ans[u]] && tmp > ans[u]))
                ans[u] = tmp;
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

    n = read();

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    dfs2(1);

    for(int i = 1; i <= n; i ++ ) printf("%d\n", len[i] - ans[i]);
    
    return 0;
}

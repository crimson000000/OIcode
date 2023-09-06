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
int v[N], din[N];
int fa[N];
int n, k, root;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int father)
{
    fa[u] = father;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;
        dfs(j, u);
    }
}

int gcd(int a, int b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

int query(int u)
{
    int p = fa[u];
    while(gcd(v[u], v[p]) == 1)
    {
        p = fa[p];
        if(p == 0) return -1;
    }
    return p;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), k = read();

    for(int i = 1; i <= n; i ++ ) v[i] = read();
    v[0] = 1;

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        din[b] ++ ;
    }

    for(int i = 1; i <= n; i ++ )
        if(!din[i])
            root = i;

    dfs(root, 0);

    while(k -- )
    {
        int op = read(), u = read();
        if(op == 1)
        {
            cout << query(u) << endl;
        }
        else
        {
            int a = read();
            v[u] = a;
        }
    }
    
    return 0;
}

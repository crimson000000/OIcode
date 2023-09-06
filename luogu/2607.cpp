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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
bool vis[N];
int v[N], fa[N];
int f[N][2];
int n, root;
ll ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dp(int u)
{
    vis[u] = true;
    f[u][1] = v[u];
    f[u][0] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j != root)
        {
            dp(j);
            f[u][1] += f[j][0];
            f[u][0] += max(f[j][0], f[j][1]);
        }
        else f[j][1] = -0x3f3f3f3f;
    }
}

void find_circle(int x)
{ 
    root = x;
    vis[root] = true;
    while(!vis[fa[root]])
    {
        root = fa[root];
        vis[root] = true;
    }
    ll t = 0;

    dp(root);
    t = max(t, (ll)max(f[root][0], f[root][1]));

    vis[root] = true;
    root = fa[root];
    dp(root);
    t = max(t, (ll)max(f[root][0], f[root][1]));

    ans += t;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        v[i] = read();
        int a = read();
        add(a, i);
        fa[i] = a;
    }

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            find_circle(i);

    cout << ans << endl;
    
    return 0;
}

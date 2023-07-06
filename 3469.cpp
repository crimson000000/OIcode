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
int siz[N];
int dfn[N], low[N], tim;
bool cut[N];
ll ans[N];
int n, m, root;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    siz[u] = 1;
    int sum = 0, cnt = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            siz[u] += siz[j];
            low[u] = min(low[u], low[j]);
            if(low[j] >= dfn[u])
            {
                cnt ++;
                if(u != root || cnt > 1) cut[u] = true;
                ans[u] += (ll)siz[j] * (n - siz[j]);
                sum += siz[j];
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }

    if(cut[u])
    {
        ans[u] += (n - 1) + (ll)(sum + 1) * (n - sum - 1);
    }
    else ans[u] = 2 * (n - 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    while(m -- )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    for(root = 1; root <= n; root ++ )
        if(!dfn[root])
            tarjan(root);

    for(int i = 1; i <= n; i ++ ) cout << ans[i] << endl;
    
    return 0;
}

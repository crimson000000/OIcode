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

const int N = 1e5 + 10, M = 2e5 + 10;
int h[N], e[M], ne[M], w[M], idx;
int sum[N];
int tr[N * 31][2], cnt[N * 31], idx2;
int n;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i], dist = w[i];
        if(j == fa) continue;
        sum[j] = sum[u] ^ dist;
        dfs(j, u);
    }
}

void insert(int x)
{
    int p = 0;
    for(int i = 30; i >= 0; i -- )
    {
        int v = x >> i & 1;
        if(!tr[p][v]) tr[p][v] = ++ idx2;
        p = tr[p][v];
    }
    cnt[p] ++;
}

int query(int x)
{
    int p = 0;
    int res = 0;
    for(int i = 30; i >= 0; i -- )
    {
        int v = x >> i & 1;
        if(tr[p][v ^ 1])
        {
            p = tr[p][v ^ 1];
            res += (1 << i);
        }
        else p = tr[p][v];
    }
    return res;
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
        int a = read(), b = read(), c = read();
        add(a, b, c), add(b, a, c);
    }

    dfs(1, 1);

    for(int i = 1; i <= n; i ++ ) insert(sum[i]);

    int maxn = 0;
    for(int i = 1; i <= n; i ++ )
    {
        maxn = max(maxn, query(sum[i]));
    }

    cout << maxn << endl;

    return 0;
}

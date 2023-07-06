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
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2510;
int a[N][N];
int h[N], e[N << 2], ne[N << 2], w[N << 2], idx;
int n;

struct edge
{
    int u, v, w;
    bool operator < (const edge& e) const
    {
        return w < e.w;
    }
}ed[N];
int cnt;

int p[N];
inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void kruskal()
{
    sort(ed + 1, ed + cnt + 1);
    ed[cnt + 1].w = -1;
    for(int i = 1; i <= n; i ++ ) p[i] = i;
    for(int l = 1, r = 0; l <= cnt; l = r + 1)
    {
        while(ed[r + 1].w == ed[l].w) r ++;
        for(int i = l; i <= r; i ++ )
            if(find(ed[i].u) == find(ed[i].v))
            {
                puts("NOT MAGIC");
                return;
            }
        for(int i = l; i <= r; i ++ )
            p[find(ed[i].u)] = find(ed[i].v);
    }
    puts("MAGIC");
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
        for(int j = 1; j <= n; j ++ )
            a[i][j] = read();
    
    for(int i = 1; i <= n; i ++ )
        if(a[i][i])
        {
            puts("NOT MAGIC");
            return 0;
        }

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j < i; j ++ )
        {
            if(a[i][j] != a[j][i])
            {
                puts("NOT MAGIC");
                return 0;
            }
            ed[++ cnt] = {i, j, a[i][j]};
        }
    }

    kruskal();

    return 0;
}
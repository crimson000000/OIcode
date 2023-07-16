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

const int N = 1e6 + 10;
struct edge
{
    int a, b, c;
    bool operator < (const edge& e) const
    {
        return c < e.c;
    }
}ed[N];
int n, m, k;
int p[N];

inline int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void kruskal()
{
    sort(ed + 1, ed + m + 1);
    for(int i = 1; i <= n; i ++ ) p[i] = i;
    int cnt = n;
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c;
        if(find(a) == find(b)) continue;
        if(c <= k)
        {
            cnt --;
            p[find(a)] = find(b);
        }
    }

    for(int i = 1; i <= n; i ++ ) p[i] = i;
    if(cnt != 1)
    {
        for(int i = 1; i <= m; i ++ ) ed[i].c = max(0, ed[i].c - k);
        sort(ed + 1, ed + m + 1);
        ll res = 0;
        for(int i = 1; i <= m; i ++ )
        {
            int a = ed[i].a, b = ed[i].b, c = ed[i].c;
            if(find(a) == find(b)) continue;
            res += c;
            p[find(a)] = find(b);
        }
        printf("%lld\n", res);
    }
    else
    {
        int maxn = 0x3f3f3f3f;
        for(int i = 1; i <= m; i ++ )
            maxn = min(maxn, abs(ed[i].c - k));

        printf("%d\n", maxn);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        n = read(), m = read(), k = read();
        for(int i = 1; i <= m; i ++ )
        {
            int a = read(), b = read(), c = read();
            ed[i] = {a, b, c};
        }

        kruskal();
    }

    return 0;
}

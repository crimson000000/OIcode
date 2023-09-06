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
    int a, b, c, id;
    bool operator < (const edge& E) const
    {
        if(c != E.c) return c < E.c;
        return id < E.id;
    }
}e[2][N];
int n, m, k, tt;
bool ans[N];

struct Union
{
    int p[N], siz[N];
    vector<pair<int&, int>> sizh, fah;
    inline void init(int n)
    {
        for(int i = 1; i <= n; i ++ ) p[i] = i, siz[i] = 1;
        sizh.clear(), fah.clear();
    }

    inline int find(int x)
    {
        while(p[x] != x) x = p[x];
        return p[x];
    }

    inline void merge(int x, int y, int op)
    {
        x = find(x), y = find(y);
        if(siz[x] > siz[y]) swap(x, y);
        if(x != y)
        {
            if(op == 0)
            {
                siz[y] += siz[x];
                p[x] = p[y];
            }
            else
            {
                sizh.push_back({siz[y], siz[y]});
                fah.push_back({p[x], p[x]});
                siz[y] += siz[x];
                p[x] = y;
            }
        }
    }

    inline void roll(int h)
    {
        while(sizh.size() > h)
        {
            fah.back().first = fah.back().second;
            fah.pop_back();
            sizh.back().first = sizh.back().second;
            sizh.pop_back();
        }
    }
}Set;

void kruskal()
{
    Set.init(n);
    int now = 1;
    for(int i = 1; i <= m; i ++ )
    {
        while(e[1][now].c == e[0][i].c)
        {
            int st = now;
            while(e[1][now].id == e[1][st].id && e[1][now].c == e[0][i].c)
            {
                int u = Set.find(e[1][now].a), v = Set.find(e[1][now].b);
                now ++;
                if(u == v)
                {
                    ans[e[1][now - 1].id] = true;
                    continue;
                }
                Set.merge(u, v, 1);
            }
            Set.roll(0);
        }
        int u = Set.find(e[0][i].a), v = Set.find(e[0][i].b);
        if(u == v) continue;
        Set.merge(u, v, 0);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        e[0][i] = {a, b, c, 0};
    }

    k = read();
    for(int i = 1; i <= k; i ++ )
    {
        int p = read();
        while(p -- )
        {
            int id = read();
            tt ++;
            e[1][tt].a = e[0][id].a, e[1][tt].b = e[0][id].b;
            e[1][tt].c = e[0][id].c, e[1][tt].id = i;
        }
    }

    sort(e[0] + 1, e[0] + m + 1);
    sort(e[1] + 1, e[1] + tt + 1);

    kruskal();

    for(int i = 1; i <= k; i ++ )
        if(ans[i]) puts("NO");
        else puts("YES");

    return 0;
}

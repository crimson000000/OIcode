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
struct item
{
    int a, d, id;
}p1[N], p2[N];
int tot1, tot2;
int n, now;

inline bool cmp1(item a, item b)
{
    return a.d < b.d;
}

inline bool cmp2(item a, item b)
{
    return a.a > b.a;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), now = read();

    for(int i = 1; i <= n; i ++ )
    {
        int d = read(), a = read();
        if(a - d >= 0) p1[++ tot1] = {a, d, i};
        else p2[++ tot2] = {a, d, i};
    }

    sort(p1 + 1, p1 + tot1 + 1, cmp1);
    sort(p2 + 1, p2 + tot2 + 1, cmp2);

    for(int i = 1; i <= tot1; i ++ )
    {
        now -= p1[i].d;
        if(now <= 0)
        {
            puts("NIE");
            return 0;
        }
        now += p1[i].a;
    }

    for(int i = 1; i <= tot2; i ++ )
    {
        now -= p2[i].d;
        if(now <= 0)
        {
            puts("NIE");
            return 0;
        }
        now += p2[i].a;
    }

    puts("TAK");
    for(int i = 1; i <= tot1; i ++ ) printf("%d ", p1[i].id);
    for(int i = 1; i <= tot2; i ++ ) printf("%d ", p2[i].id);

    return 0;
}

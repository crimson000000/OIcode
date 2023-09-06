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

const int N = 1e6 + 10;
struct P
{
    int id, x, y;
    P() {}
    P(int _i, int _x, int _y): id(_i), x(_x), y(_y) {}
    bool operator < (const P& a) const
    {
        if(x != a.x) return x < a.x;
        if(y != a.y) return y < a.y;
        return id < a.id;
    }
}p[N];
int a[N], f[N];
int ans[N];
int n, m, k;
int h, cur;

struct ta
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    h = -1;
    for(int i = 1; i <= n; i ++ )
    {
        int x = read(), y = read();
        p[i] = P(0, x, y);
        a[i] = y;
    }

    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read();
        p[i + n] = P(i, x, y);
    }

    sort(p + 1, p + n + m + 1);
    sort(a + 1, a + n + 1);
    k = unique(a + 1, a + n + 1) - a - 1;

    for(int i = 1; i <= n + m; i ++ )
    {
        if(p[i].id)
        {
            if(!p[i - 1].id && p[i].x == p[i - 1].x && p[i].y == p[i - 1].y)
                ans[p[i].id] = 1;
            else if(p[i].x != h)
            {
                int y = upper_bound(a + 1, a + k + 1, p[i].y) - a - 1;
                if((p[i].y != a[y] || !f[y]) && p[i].y + cur - bit.query(y) == p[i].x)
                    ans[p[i].id] = 1;
            }
        }
        else
        {
            int y = lower_bound(a + 1, a + k + 1, p[i].y) - a;
            int d = cur - bit.query(y), z = p[i].x - p[i].y;
            if(z < d)
            {
                if(!f[y]) f[y] = 1, bit.add(y, 1);
            }
            else if(z > d && h != p[i].x)
                h = p[i].x, cur ++;
        }
    }

    for(int i = 1; i <= m; i ++ )
        if(ans[i]) puts("LOSE");
        else puts("WIN");

    return 0;
}

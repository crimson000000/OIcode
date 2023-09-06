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
struct boots_snow
{
    int f_s;
    int can_place;
    int id;
    bool boots;
    bool operator < (const boots_snow& a) const
    {
        if(f_s != a.f_s) return f_s < a.f_s;
        return boots < a.boots;
    }
}a[N];

struct segmenttree
{
    struct seg
    {
        int l, r;
        int len;
        int lmax, rmax, maxn;
    }t[N << 2];

    inline void pushup(int p, int l, int r)
    {
        t[p].len = t[l].len + t[r].len;
        t[p].lmax = t[l].lmax;
        if(t[l].len == t[l].maxn) 
            t[p].lmax = max(t[l].len + t[r].lmax, t[p].lmax);
        t[p].rmax = t[r].rmax;
        if(t[r].len == t[r].maxn) 
            t[p].rmax = max(t[r].len + t[l].rmax, t[p].rmax);
        t[p].maxn = max(max(t[l].maxn, t[r].maxn), t[l].rmax + t[r].lmax);
    }

    inline void pushup(int p)
    {
        pushup(p, p << 1, p << 1 | 1);
    }

    inline void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) 
        {
            t[p].lmax = t[p].rmax = t[p].maxn = 0;
            t[p].len = 1;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void change(int p, int pos)
    {
        if(t[p].l == t[p].r)
        {
            t[p].lmax = t[p].rmax = t[p].maxn = 1;
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) change(p << 1, pos);
        else change(p << 1 | 1, pos);
        pushup(p);
    }

    inline int query()
    {
        return t[1].maxn;
    }
}t;

int n, b, cnt;
bool ans[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), b = read();
    for(int i = 1; i <= n; i ++ )
    {
        int f = read();
        a[++ cnt].f_s = f;
        a[cnt].can_place = i;
        a[cnt].boots = false;
    }

    for(int i = 1; i <= b; i ++ )
    {
        int s = read(), d = read();
        a[++ cnt].f_s = s;
        a[cnt].can_place = d;
        a[cnt].id = i;
        a[cnt].boots = true;
    }

    t.build(1, 1, n);

    sort(a + 1, a + cnt + 1);
    reverse(a + 1, a + cnt + 1);

    for(int i = 1; i <= cnt; i ++ )
    {
        if(!a[i].boots)
        {
            t.change(1, a[i].can_place);
        }
        else
        {
            int maxd = t.query();
            // printf("%d %d\n", a[i].f_s, maxd);
            if(a[i].can_place > maxd) ans[a[i].id] = true;
            else ans[a[i].id] = false;
        }
    }

    for(int i = 1; i <= b; i ++ ) 
        if(ans[i])
            puts("1");
        else puts("0");

    return 0;
}
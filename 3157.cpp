#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) x & -x
#define int long long
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e5 + 10;

int n, m;
struct tree_array
{
    int c[N];

    inline void add(int x, int val)
    {
        for (; x <= n; x += lowbit(x))
            c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x))
            res += c[x];
        return res;
    }

    inline void clear(int x)
    {
        for(; x <= n; x += lowbit(x)) c[x] = 0;
    }
} bit;

struct ele
{
    int pos, val, time;

    bool operator < (const ele& E) const
    {
        if(pos == E.pos) return val < E.val;
        return pos < E.pos;
    }
} a[N << 1], tmp[N << 1];
int pos[N], ans[N];

bool cmp1(ele a, ele b)
{
    return a.time < b.time;
}

void solve(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    solve(l, mid), solve(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while(i <= mid || j <= r)
    {
        if(j > r || (i <= mid && a[i] < a[j]))
        {
            bit.add(a[i].val, 1);
            tmp[k ++ ] = a[i ++ ];
        }
        else
        {
            ans[a[j].time] += bit.query(n) - bit.query(a[j].val);
            tmp[k ++ ] = a[j ++ ];
        }
    }

    for(int i = l; i <= mid; i ++ ) bit.clear(a[i].val);
    for(int i = l; i <= r; i ++ ) a[i] = tmp[i];
    for(int i = r; i >= l; i -- )
        if(a[i].time <= mid) bit.add(a[i].val, 1);
        else ans[a[i].time] += bit.query(a[i].val);

    // printf("%d %d: ", l, r);
    // for(int i = l; i <= r; i ++ )
    // {
    //     printf("[%d %d %d]", a[i].val, a[i].pos, a[i].time);
    // }
    // puts("");

    // for(int i = 1; i <= n; i ++ )
    //     printf("%d ", ans[i]);
    // puts("");
    
    for(int i = r; i >= l; i -- ) bit.clear(a[i].val);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for (int i = 1; i <= n; i++)
    {
        int x = read();
        a[i] = {i, x, 0};
        pos[x] = i;
    }

    int tim = n;

    for (int i = m; i; i--)
    {
        int x = read();
        a[pos[x]].time = tim --;
    }

    for(int i = 1; i <= n; i ++ )
        if(!a[i].time)
            a[i].time = tim --;

    sort(a + 1, a + n + 1, cmp1);
    solve(1, n);

    for(int i = 1; i <= n; i ++ ) ans[i] += ans[i - 1];
    for(int i = n; i >= n - m + 1; i -- ) printf("%lld\n", ans[i]);

    return 0;
}

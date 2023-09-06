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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, tt, id;

struct tree_array
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
} bit;

struct Q
{
    int op, x, y, k;
}q[N], lq[N], rq[N];

int ans[N], a[N];

void solve(int lval, int rval, int st, int ed)
{
    if(st > ed) return;
    if(lval == rval)
    {
        for(int i = st; i <= ed; i ++ )
            if(q[i].op > 0) 
                ans[q[i].op] = lval;
        return;
    }

    int mid = lval + rval >> 1;
    int lt = 0, rt = 0;
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op <= 0)
        {
            if(q[i].y <= mid) bit.add(q[i].x, q[i].k), lq[++ lt] = q[i];
            else rq[++ rt] = q[i];
        }
        else
        {
            int l = q[i].x, r = q[i].y;
            int cnt = bit.query(r) - bit.query(l - 1);
            if(cnt >= q[i].k) lq[++ lt] = q[i];
            else q[i].k -= cnt, rq[++ rt] = q[i];
        }
    }

    for(int i = st; i <= ed; i ++ )
        if(q[i].op <= 0 && q[i].y <= mid)
            bit.add(q[i].x, -q[i].k);
    
    for(int i = 1; i <= lt; i ++ ) q[i + st - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[i + lt + st - 1] = rq[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        q[++ tt] = {0, i, a[i], 1};
    }

    for(int i = 1; i <= m; i ++ )
    {
        char op[5];
        scanf("%s", op);
        
        if(op[0] == 'Q')
        {
            int l = read(), r = read(), k = read();
            q[++ tt] = {++ id, l, r, k};
        }
        else
        {
            int x = read(), y = read();
            q[++ tt] = {-1, x, a[x], -1};
            q[++ tt] = {0, x, y, 1};
            a[x] = y;
        }
    }

    solve(-INF, INF, 1, tt);

    for(int i = 1; i <= id; i ++ )
        printf("%d\n", ans[i]);
    
    return 0;
}

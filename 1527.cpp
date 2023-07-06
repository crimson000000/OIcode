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

const int N = 510, M = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m;

struct tree_array
{
    int c[N][N];
    #define lowbit(x) x & -x

    inline void add(int x, int y, int val)
    {
        for(int i = x; i <= n; i += lowbit(i))
            for(int j = y; j <= n; j += lowbit(j))
                c[i][j] += val;
    }

    inline int query(int x, int y)
    {
        if(!x || !y) return 0;
        int res = 0;
        for(int i = x; i; i -= lowbit(i))
            for(int j = y; j; j -= lowbit(j))
                res += c[i][j];
        return res;
    }

    inline int ask(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
} bit;

struct Q
{
    int op, x1, y1, x2, y2, k;
}q[M], lq[M], rq[M];
int ans[M];
int tt;

void solve(int lval, int rval, int st, int ed)
{
    if(st > ed) return;
    if(lval == rval)
    {
        for(int i = st; i <= ed; i ++ )
            if(q[i].op != 0)
                ans[q[i].op] = lval;
        return;
    }
    int mid = lval + rval >> 1;
    int lt = 0, rt = 0;
    for(int i = st; i <= ed; i ++ )
    {
        if(q[i].op == 0)
        {
            if(q[i].k <= mid) bit.add(q[i].x1, q[i].y1, 1), lq[++ lt] = q[i];
            else rq[++ rt] = q[i];
        }
        else
        {
            int cnt = bit.ask(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
            if(cnt >= q[i].k) lq[++ lt] = q[i];
            else q[i].k -= cnt, rq[++ rt] = q[i];
        }
    }

    for(int i = st; i <= ed; i ++ )
        if(q[i].op == 0 && q[i].k <= mid)
            bit.add(q[i].x1, q[i].y1, -1);
    
    for(int i = 1; i <= lt; i ++ ) q[i + st - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[st + lt + i - 1] = rq[i];

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
        for(int j = 1; j <= n; j ++ )
        {
            int val = read();
            q[++ tt] = {0, i, j, i, j, val};
        }
    

    for(int i = 1; i <= m; i ++ )
    {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read(), k = read();
        q[++ tt] = {i, x1, y1, x2, y2, k};
    }

    solve(-INF, INF, 1, tt);

    for(int i = 1; i <= m; i ++ )
        printf("%d\n", ans[i]);
    
    return 0;
}

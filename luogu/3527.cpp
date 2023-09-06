#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
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

const int N = 1e6 + 10;
int n, m, k;
int c[N], p[N], ans[N];

struct tree_array
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int val)
    {
        for(; x <= m * 2; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
} bit;

struct C
{
    int x, y, val;
}ch[N];

struct Q
{
    int c, k, h;
}q[N], lq[N], rq[N];

int e[N], ne[N], idx;

void add(int a, int b)
{
    e[++ idx] = b, ne[idx] = q[a].h, q[a].h = idx;
}

void solve(int lval, int rval, int st, int ed)
{
    if(st > ed) return;
    if(lval == rval)
    {
        for(int i = st; i <= ed; i ++ )
            ans[q[i].c] = lval;
        return;
    }

    int mid = lval + rval >> 1, lt = 0, rt = 0;
    // cout << mid << endl;
    for(int i = lval; i <= mid; i ++ ) 
    {
        bit.add(ch[i].x, ch[i].val), bit.add(ch[i].y + 1, -ch[i].val);
    }

    for(int i = st; i <= ed; i ++ )
    {
        int cnt = 0;
        for(int k = q[i].h; k && cnt <= q[i].k; k = ne[k])
        {
            int j = e[k];
            cnt += bit.query(j) + bit.query(j + m);
        }
        if(cnt >= q[i].k) lq[++ lt] = q[i];
        else q[i].k -= cnt, rq[++ rt] = q[i];
    }
    
    for(int i = lval; i <= mid; i ++ )
        bit.add(ch[i].x, -ch[i].val), bit.add(ch[i].y + 1, ch[i].val);

    for(int i = 1; i <= lt; i ++ ) q[i + st - 1] = lq[i];
    for(int i = 1; i <= rt; i ++ ) q[i + st + lt - 1] = rq[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ ) 
    {
        c[i] = read();
        add(c[i], i);
    }

    for(int i = 1; i <= n; i ++ )
    {
        q[i].k = read();
        q[i].c = i;
    }

    k = read();
    for(int i = 1; i <= k; i ++ )
    {
        int l = read(), r = read(), val = read();
        if(r < l) r += m;
        ch[i] = {l, r, val};
        // printf("%d %d %d %d\n", i, ch[i].x, ch[i].y, ch[i].val);
    }

    solve(1, k + 1, 1, n);

    for(int i = 1; i <= n; i ++ )
        if(ans[i] == k + 1) puts("NIE");
        else printf("%d\n", ans[i]);
    
    return 0;
}

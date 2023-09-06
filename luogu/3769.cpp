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
struct poi
{
    int x[4];
}q[N];
int n;

inline bool cmp1(int a, int b) {return q[a].x[0] < q[b].x[0];}
inline bool cmp2(int a, int b) {return q[a].x[1] < q[b].x[1];}
inline bool cmp3(int a, int b) {return q[a].x[2] < q[b].x[2];}
inline bool cmp4(poi a, poi b) 
{
    if(a.x[3] != b.x[3]) return a.x[3] < b.x[3];
    for(int i = 0; i < 3; i ++ )
        if(a.x[i] != b.x[i])
            return a.x[i] < b.x[i];
    return false;
}

struct kdt
{
    int l, r;
    int maxd[3], mind[3];
    int val;
    int maxval;
}t[N];
int g[N];
int rt;

inline void pushup(int p)
{
    for(int i = 0; i < 3; i ++ ) t[p].maxd[i] = t[p].mind[i] = q[p].x[i];
    if(t[p].l)
    {
        for(int i = 0; i < 3; i ++ )
        {
            t[p].maxd[i] = max(t[p].maxd[i], t[t[p].l].maxd[i]);
            t[p].mind[i] = min(t[p].mind[i], t[t[p].l].mind[i]);
        }
    }
    if(t[p].r)
    {
        for(int i = 0; i < 3; i ++ )
        {
            t[p].maxd[i] = max(t[p].maxd[i], t[t[p].r].maxd[i]);
            t[p].mind[i] = min(t[p].mind[i], t[t[p].r].mind[i]);
        }
    }
}

inline int build(int l, int r, int op)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    if(op == 0)
    {
        nth_element(g + l, g + mid, g + r + 1, cmp1);
        t[g[mid]].l = build(l, mid - 1, 1);
        t[g[mid]].r = build(mid + 1, r, 1);
        pushup(g[mid]);
    }
    if(op == 1)
    {
        nth_element(g + l, g + mid, g + r + 1, cmp2);
        t[g[mid]].l = build(l, mid - 1, 2);
        t[g[mid]].r = build(mid + 1, r, 2);
        pushup(g[mid]);
    }
    if(op == 2)
    {
        nth_element(g + l, g + mid, g + r + 1, cmp3);
        t[g[mid]].l = build(l, mid - 1, 0);
        t[g[mid]].r = build(mid + 1, r, 0);
        pushup(g[mid]);
    }
    return g[mid];
}

inline bool is_in(int x[], int y[])
{
    int cnt = 0;
    for(int i = 0; i < 3; i ++ ) cnt += (x[i] <= y[i]);
    return cnt == 3;
}

int tmp;
inline void query(int p, int x)
{
    if(t[p].maxval <= tmp) return;
    if(!is_in(t[p].mind, q[x].x)) return;
    if(is_in(t[p].maxd, q[x].x))
    {
        tmp = t[p].maxval;
        return;
    }
    if(is_in(q[p].x, q[x].x)) tmp = max(tmp, t[p].val);
    if(t[p].l) query(t[p].l, x);
    if(t[p].r) query(t[p].r, x);
}

inline void upit(int p, int y)
{
    if(p == y)
    {
        t[p].val = tmp;
        t[p].maxval = max(t[p].val, t[p].maxval);
        return;
    }
    if(!is_in(q[y].x, t[p].maxd) || !is_in(t[p].mind, q[y].x)) return;
    if(t[p].l) upit(t[p].l, y);
    if(t[p].r) upit(t[p].r, y);
    t[p].maxval = max(t[p].maxval, max(t[t[p].l].maxval, t[t[p].r].maxval));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        g[i] = i;
        for(int j = 0; j < 4; j ++ )
            q[i].x[j] = read();
    }

    sort(q + 1, q + n + 1, cmp4);
    rt = build(1, n, 0);

    int ans = 0;
    for(int i = 1; i <= n; i ++ )
    {
        tmp = 0;
        query(rt, i);
        tmp ++;
        upit(rt, i);
        ans = max(ans, tmp);
    }

    cout << ans << endl;

    return 0;
}

#include <bits/stdc++.h>
typedef int it;
#define int long long
using namespace std;
const int N = 1e5 + 10;

int n, w, h, cnt;
struct seg
{
    int x, y1, y2, val;
    bool operator< (const seg& W) const
    {
        if(x != W.x) return x < W.x;
        return val > W.val;
    }
}segs[N * 4];

struct segmenttree
{
    int l, r;
    int maxn, add;
}t[N * 4];
int nums[N << 1];

int find(int x)
{
    return lower_bound(nums + 1, nums + cnt + 1, x) - nums;
}

void init()
{
    memset(segs, 0, sizeof segs);
    memset(t, 0, sizeof t);
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].maxn = t[p].add = 0;
    if(l == r)
    {
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void pushup(int p)
{
    t[p].maxn = max(t[p << 1].maxn, t[p << 1 | 1].maxn);
}

void pushdown(int p)
{
    t[p << 1].maxn += t[p].add;
    t[p << 1 | 1].maxn += t[p].add;
    t[p << 1].add += t[p].add;
    t[p << 1 | 1].add += t[p].add;
    t[p].add = 0;
    
}

void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].maxn += val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

it main()
{
    int T;
    scanf("%lld", &T);
    while(T -- )
    {
        init();
        scanf("%lld%lld%lld", &n, &w, &h);
        for(int i = 1; i <= n; i ++ )
        {
            int x, y, l;
            scanf("%lld%lld%lld", &x, &y, &l);
            nums[(i << 1) - 1] = y;
            nums[i << 1] = y + h - 1;
            segs[(i << 1) - 1] = {x, y, y + h - 1, l};
            segs[i << 1] = {x + w - 1, y, y + h - 1, -l};
        }

        sort(segs + 1, segs + 2 * n + 1);
        sort(nums + 1, nums + 2 * n + 1);
        cnt = unique(nums + 1, nums + 2 * n + 1) - nums - 1;

        for(int i = 1; i <= 2 * n; i ++ )
        {
            int pos1 = find(segs[i].y1);
            int pos2 = find(segs[i].y2);
            segs[i].y1 = pos1;
            segs[i].y2 = pos2;
        }
        build(1, 1, cnt);

        int ans = 0;
        for(int i = 1; i <= 2 * n; i ++ )
        {
            change(1, segs[i].y1, segs[i].y2, segs[i].val);
            ans = max(ans, t[1].maxn);
        }
        cout << ans << endl;
    }
    return 0;
}
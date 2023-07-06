#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef double ld;

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
int f1[N], f2[N];
double g1[N], g2[N], sum;
int n;
vector<int> nums;

struct node
{
    int a, b, t;
}a[N], tmp[N];

inline bool cmp1(node x, node y)
{
    return x.a > y.a;
}

inline bool cmp2(node x, node y)
{
    return x.b < y.b;
}

inline bool cmp3(node x, node y)
{
    return x.t < y.t;
}

namespace sgm
{
    struct segment
    {
        int l, r;
        int val;
        double cnt;
    }t[N << 2];
    int root, cnt;

    inline void clear(int p, int l, int r)
    {
        if(!p) return;
        int mid = l + r >> 1;
        clear(t[p].l, l, mid);
        clear(t[p].r, mid + 1, r);
        t[p].l = t[p].r = t[p].val = t[p].cnt = 0;
    }

    inline void pushup(int p)
    {
        if(t[t[p].l].val > t[t[p].r].val)
        {
            t[p].val = t[t[p].l].val;
            t[p].cnt = t[t[p].l].cnt;
        }
        else if(t[t[p].l].val < t[t[p].r].val)
        {
            t[p].val = t[t[p].r].val;
            t[p].cnt = t[t[p].r].cnt;
        }
        else
        {
            t[p].val = t[t[p].l].val;
            t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
        }
    }

    inline void insert(int &p, int l, int r, int pos, int val, double v)
    {
        if(!p) 
        {
            p = ++ cnt;
        }
        if(l == r)
        {
            if(t[p].val < val) t[p].val = val, t[p].cnt = 0;
            if(t[p].val == val) t[p].cnt += v;
            return;
        }
        int mid = l + r >> 1;
        if(pos <= mid) insert(t[p].l, l, mid, pos, val, v);
        else insert(t[p].r, mid + 1, r, pos, val, v);
        pushup(p);
    }

    inline int query(int p, int l, int r, int L, int R, double &cntt)
    {
        if(!p || r < L || l > R) 
        {
            cntt = 0;
            return 0;
        }
        if(l >= L && r <= R) 
        {
            cntt = t[p].cnt;
            return t[p].val;
        }
        int mid = l + r >> 1;
        double cntl = 0, cntr = 0;
        int al = query(t[p].l, l, mid, L, R, cntl);
        int ar = query(t[p].r, mid + 1, r, L, R, cntr);
        cntt = 0;
        if(l <= mid && max(al, ar) == al) cntt += cntl;
        if(r > mid && max(al, ar) == ar) cntt += cntr;
        return max(al, ar);
    }

    inline void clear()
    {
        clear(root, 1, n);
        root = 0, cnt = 0;
    }
}

using namespace sgm;

void cdq(int l, int r, int f[], double g[])
{
    if(l == r) return;
    int mid = l + r >> 1;
    sort(a + l, a + r + 1, cmp3);

    cdq(l, mid, f, g);

    sort(a + l, a + mid + 1, cmp1);
    sort(a + mid + 1, a + r + 1, cmp1);

    clear();
    for(int x = l, y = mid + 1; y <= r; y ++ )
    {
        while(a[x].a >= a[y].a && x <= mid)
        {
            insert(root, 1, n, a[x].b, f[a[x].t], g[a[x].t]);
            x ++;
        }
        double cn = 0;
        int fx = query(root, 1, n, a[y].b, n, cn);
        if(!fx) continue;
        if(fx + 1 > f[a[y].t])
        {
            f[a[y].t] = fx + 1;
            g[a[y].t] = 0;
        }
        if(fx + 1 == f[a[y].t])
        {
            g[a[y].t] += cn;
        }
    }

    cdq(mid + 1, r, f, g);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();
    int maxa = 0;
    for(int i = 1; i <= n; i ++ )
    {
        a[i].a = read(), a[i].b = read();
        maxa = max(maxa, a[i].a);
        a[i].t = i;
        nums.push_back(a[i].b);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
    {
        a[i].b = lower_bound(nums.begin(), nums.end(), a[i].b) - nums.begin() + 1;
        f1[i] = 1, g1[i] = 1;
        f2[i] = 1, g2[i] = 1;
    }

    cdq(1, n, f1, g1);

    for(int i = 1; i <= n; i ++ )
    {
        a[i].t = n - a[i].t + 1;
        a[i].a = maxa - a[i].a + 1;
        a[i].b = n - a[i].b + 1;
    }

    sort(a + 1, a + n + 1, cmp3);

    cdq(1, n, f2, g2);

    int ans1 = 0;
    for(int i = 1; i <= n; i ++ ) ans1 = max(ans1, f1[i]);

    cout << ans1 << endl;

    for(int i = 1; i <= n; i ++ )
        if(f1[i] == ans1)
            sum += g1[i];

    for(int i = 1; i <= n; i ++ )
    {
        if(f1[i] + f2[n - i + 1] - 1 == ans1)
        {
            printf("%.5lf ", g1[i] * g2[n - i + 1] / sum);
        }
        else printf("0.00000 ");
    }

    return 0;
}

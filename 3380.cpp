#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

namespace INPUT_SPACE
{
    const int S = (1 << 20) + 5;
    char B[S], *H, *T;
    inline int gc()
    {
        if (H == T)
            T = (H = B) + fread(B, 1, S, stdin);
        return (H == T) ? EOF : *H++;
    }
    inline unsigned int read()
    {
        unsigned int x, ch;
        while ((ch = gc()) < '0' || ch > '9')
            ;
        x = ch ^ '0';
        while ((ch = gc()) >= '0' && ch <= '9')
            x = x * 10 + (ch ^ '0');
        return x;
    }
}
using INPUT_SPACE::read;

const int INF = 2147483647;

namespace tree
{
    const int N = 4e5 + 10;
    struct node
    {
        int l, r;
        int val, key, siz;
    } t[N * 20];
    int cnt;

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    }

    inline int New(int val)
    {
        t[++cnt].val = val;
        t[cnt].key = rand();
        t[cnt].siz = 1;
        return cnt;
    }

    inline int merge(int x, int y)
    {
        if (!x || !y)
            return x + y;
        if (t[x].key < t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            pushup(x);
            return x;
        }
        else
        {
            t[y].l = merge(x, t[y].l);
            pushup(y);
            return y;
        }
    }

    inline void split(int p, int val, int &x, int &y)
    {
        if (!p)
            x = y = 0;
        else
        {
            if (t[p].val <= val)
            {
                x = p;
                split(t[p].r, val, t[x].r, y);
            }
            else
            {
                y = p;
                split(t[p].l, val, x, t[y].l);
            }
            pushup(p);
        }
    }

    int x, y, z;
    inline void insert(int &root, int val)
    {
        split(root, val, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline void del(int &root, int val)
    {
        split(root, val - 1, x, y);
        split(y, val, y, z);
        y = merge(t[y].l, t[y].r);
        root = merge(merge(x, y), z);
    }

    inline int getpre(int &root, int val)
    {
        split(root, val - 1, x, y);
        int ret;
        if (!t[x].siz)
            ret = -INF;
        else
        {
            int p = x;
            while (t[p].r)
                p = t[p].r;
            ret = t[p].val;
        }
        root = merge(x, y);
        return ret;
    }

    inline int getnxt(int &root, int val)
    {
        split(root, val, x, y);
        int ret;
        if (t[y].siz)
        {
            int p = y;
            while (t[p].l)
                p = t[p].l;
            ret = t[p].val;
        }
        else
            ret = INF;
        root = merge(x, y);
        return ret;
    }

    inline int getrank(int &root, int val)
    {
        int p = root, ret = 0;
        while(p)
        {
            if(t[p].val < val) ret += t[t[p].l].siz + 1, p = t[p].r;
            else p = t[p].l;
        }
        return ret + 1;
    }

    inline int getval(int &root, int rk)
    {
        int p = root;
        while (1)
        {
            if (t[t[p].l].siz + 1 == rk)
                return t[p].val;
            else if (t[t[p].l].siz + 1 > rk)
                p = t[p].l;
            else
            {
                rk -= t[t[p].l].siz + 1;
                p = t[p].r;
            }
        }
    }
}

const int N = 1e5 + 10;

struct segment
{
    int l, r;
    int root;
} t[N * 4];
int a[N];

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    for (register int i = l; i <= r; i++)
        tree::insert(t[p].root, a[i]);
    if (l == r)
        return;

    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline int query_rank(int p, int l, int r, int val)
{
    if (t[p].r < l || t[p].l > r)
        return 0;
    if (t[p].l >= l && t[p].r <= r)
        return tree::getrank(t[p].root, val) - 1;
    int mid = t[p].l + t[p].r >> 1;
    int rk = 0;
    if (l <= mid)
        rk += query_rank(p << 1, l, r, val);
    if (r > mid)
        rk += query_rank(p << 1 | 1, l, r, val);
    return rk;
}

inline int query_val(int l, int r, int rk)
{
    int L = 0, R = 1e8, ans = -1;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (query_rank(1, l, r, mid) + 1 <= rk)
            L = mid + 1, ans = mid;
        else
            R = mid - 1;
    }
    return ans;
}

inline void change(int p, int pos, int val)
{
    tree::del(t[p].root, a[pos]);
    tree::insert(t[p].root, val);
    if (t[p].l == t[p].r)
        return;
    int mid = t[p].l + t[p].r >> 1;
    if (pos <= mid)
        change(p << 1, pos, val);
    else
        change(p << 1 | 1, pos, val);
}

inline int get_pre(int p, int l, int r, int val)
{
    if (t[p].r < l || t[p].l > r)
        return -INF;
    if (t[p].l >= l && t[p].r <= r)
        return tree::getpre(t[p].root, val);
    int mid = t[p].l + t[p].r >> 1;
    int pre = -INF;
    if (l <= mid)
        pre = max(pre, get_pre(p << 1, l, r, val));
    if (r > mid)
        pre = max(pre, get_pre(p << 1 | 1, l, r, val));
    return pre;
}

inline int get_next(int p, int l, int r, int val)
{
    if (t[p].r < l || t[p].l > r)
        return INF;
    if (t[p].l >= l && t[p].r <= r)
        return tree::getnxt(t[p].root, val);
    int mid = t[p].l + t[p].r >> 1;
    int nxt = INF;
    if (l <= mid)
        nxt = min(nxt, get_next(p << 1, l, r, val));
    if (r > mid)
        nxt = min(nxt, get_next(p << 1 | 1, l, r, val));
    return nxt;
}

int n, m;
int maxval, minval = 0x3f3f3f3f;

int main()
{
#ifdef LOCAL
    freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
    freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
#endif
    n = read(), m = read();
    for (register int i = 1; i <= n; i++)
    {
        a[i] = read();
    }

    build(1, 1, n);

    while (m--)
    {
        int opt, l, r, k, pos;
        opt = read();
        switch (opt)
        {
        case 1:
            l = read(), r = read(), k = read();
            printf("%d\n", query_rank(1, l, r, k) + 1);
            break;
        case 2:
            l = read(), r = read(), k = read();
            printf("%d\n", query_val(l, r, k));
            break;
        case 3:
            pos = read(), k = read();
            change(1, pos, k);
            a[pos] = k;
            break;
        case 4:
            l = read(), r = read(), k = read();
            printf("%d\n", get_pre(1, l, r, k));
            break;
        case 5:
            l = read(), r = read(), k = read();
            printf("%d\n", get_next(1, l, r, k));
            break;
        }
    }
    return 0;
}

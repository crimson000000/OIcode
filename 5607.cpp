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

const int N = 5e4 + 10;
int n, m;
int a[N], b[N];

struct base
{
    int d[33];

    void init()
    {
        memset(d, 0, sizeof d);
    }

    void insert(int x)
    {
        for(int i = 30; i >= 0; i -- )
        {
            if(x >> i & 1)
            {
                if(!d[i])
                {
                    d[i] = x;
                    return;
                }
                x ^= d[i];
            }
        }
    }
};

base merge(base a, base b)
{
    base c = a;
    for(int i = 30; i >= 0; i -- )
    {
        int x = b.d[i];
        if(!x) continue;
        c.insert(x);
    }  
    return c;
}

struct segmenttree
{
    struct segment
    {
        int l, r;
        base a;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].a = merge(t[p << 1].a, t[p << 1 | 1].a);
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r)
        {
            t[p].a.insert(b[l]);
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    void change(int p, int pos, int x)
    {
        if(t[p].l == t[p].r)
        {
            t[p].a.init();
            b[pos] ^= x;
            t[p].a.insert(b[pos]);
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) change(p << 1, pos, x);
        else change(p << 1 | 1, pos, x);
        pushup(p);
    }

    base query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].a;
        int mid = t[p].l + t[p].r >> 1;
        base res;
        res.init();
        if(l <= mid) res = merge(res, query(p << 1, l, r));
        if(r > mid) res = merge(res, query(p << 1 | 1, l, r));
        return res;
    }
}t;

struct treearray
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int v)
    {
        for(; x <= n; x += lowbit(x)) c[x] ^= v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res ^= c[x];
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
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        b[i] = a[i] ^ a[i - 1];
        bit.add(i, b[i]);
    }

    t.build(1, 1, n);

    while(m -- )
    {
        int op = read(), l = read(), r = read(), v = read();
        if(op == 1)
        {
            t.change(1, l, v), bit.add(l, v);
            if(r != n) t.change(1, r + 1, v), bit.add(r + 1, v);
        }
        else
        {
            if(l == r)
            {
                int k = bit.query(l);
                v = max(v, v ^ k);
            }
            else
            {
                auto k = t.query(1, l + 1, r);
                k.insert(bit.query(l));
                for(int i = 30; i >= 0; i -- )
                    v = max(v, v ^ k.d[i]);
            }
            printf("%d\n", v);
        }
    }
    
    return 0;
}

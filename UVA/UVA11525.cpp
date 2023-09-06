#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int n;
int a[N];
struct fhq
{
    struct node
    {
        int l, r;
        int val, key, siz;
    }t[N];
    int root, cnt;

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    }

    inline int New(int val)
    {
        t[++ cnt].val = val;
        t[cnt].siz = 1;
        t[cnt].key = rand();
        t[cnt].l = t[cnt].r = 0;
        return cnt;
    }

    inline void split(int p, int val, int &x, int &y)
    {
        if(!p) x = y = 0;
        else
        {
            if(t[p].val <= val)
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

    inline int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key < t[y].key)
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

    int x, y, z;
    inline void insert(int val)
    {
        split(root, val, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline void del(int val)
    {
        split(root, val - 1, x, y);
        split(y, val, y, z);
        y = merge(t[y].l, t[y].r);
        root = merge(merge(x, y), z);
    }
    
    inline int kth(int val)
    {
        int p = root, res = 0;
        while(p)
        {
            if(t[p].val > val) p = t[p].l;
            else 
            {
                res += t[t[p].l].siz + 1;
                p = t[p].r;
            }
        }
        return res;
    }

    inline int getval(int rk)
    {
        int p = root;
        while(1)
        {
            if(t[t[p].l].siz >= rk) p = t[p].l;
            else if(t[t[p].l].siz + 1 == rk) return t[p].val;
            else 
            {
                rk -= t[t[p].l].siz + 1;
                p = t[p].r;
            }
        }
    }

    inline void clear()
    {
        root = 0;
        cnt = 0;
    }
}t;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        t.clear();
        n = read();
        for(int i = 1; i <= n; i ++ ) a[i] = read() + 1, t.insert(i);

        for(int i = 1; i <= n; i ++ )
        {
            int pos = t.getval(a[i]);
            printf("%d", pos);
            t.del(pos);
            if(i != n) putchar(' ');
        }
        puts("");
    }

    return 0;
}

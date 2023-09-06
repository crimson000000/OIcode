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

const int N = 1e6 + 10, S = 1000, M = 5e5 + 10;
struct Query
{
    int op, l, r, x;
}q[M];
int ans[M];
int L[N], R[N], pos[N];
int a[N];
int n, m;

struct Block
{
    int l, r, tag, mx;
    int fa[N], rt[N], val[N], siz[N];

    inline int find(int x)
    {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }

    inline void merge(int x, int y)
    {
        if(rt[y])
        {
            fa[rt[x]] = rt[y];
        }
        else
        {
            rt[y] = rt[x];
            val[rt[y]] = y;
        }
        siz[y] += siz[x];
        rt[x] = siz[x] = 0;
    }

    inline void destroy()
    {
        for(int i = l; i <= r; i ++ )
        {
            a[i] = val[find(i)];
            rt[a[i]] = 0;
            siz[a[i]] = 0;
            a[i] -= tag;
        }
        for(int i = l; i <= r; i ++ ) fa[i] = 0;
        tag = 0;
    }

    inline void build()
    {
        mx = 0;
        for(int i = l; i <= r; i ++ )
        {
            if(!rt[a[i]])
            {
                rt[a[i]] = i;
                fa[i] = i;
                val[i] = a[i];
            }
            else fa[i] = rt[a[i]];
            siz[a[i]] ++;
            mx = max(mx, a[i]);
        }
    }

    inline void totalchange(int x)
    {
        if(mx - tag >= (x << 1))
        {
            for(int i = tag + 1; i <= tag + x; i ++ )
                if(rt[i])
                    merge(i, i + x);
            tag += x;
        }
        else
        {
            for(int i = mx; i > tag + x; i -- )
                if(rt[i])
                    merge(i, i - x);
            mx = min(mx, tag + x);
        }
    }

    inline void partchange(int ll, int rr, int x)
    {
        if(ll > rr) return;
        destroy();
        for(int i = ll; i <= rr; i ++ )
            if(a[i] > x)
                a[i] -= x;
        build();
    }

    inline int totalquery(int x)
    {
        if(x + tag > 500000) return 0;
        return siz[tag + x];
    }

    inline int partquery(int ll, int rr, int x)
    {
        int ans = 0;
        for(int i = ll; i <= rr; i ++ )
            if(val[find(i)] - tag == x) ans ++;
        return ans;
    }
}blk;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= m; i ++ ) 
    {
        int op = read(), l = read(), r = read(), x = read();
        q[i] = {op, l, r, x};
    }

    for(int i = 1; i <= n; i ++ ) pos[i] = (i - 1) / S + 1;
    for(int i = 1; i <= pos[n]; i ++ )
    {
        L[i] = (i - 1) * S + 1;
        R[i] = min(i * S, n);
    }
    
    for(int i = 1; i <= pos[n]; i ++ )
    {
        blk.l = L[i], blk.r = R[i];
        blk.build();
        for(int j = 1; j <= m; j ++ )
        {
            int l = q[j].l, r = q[j].r, x = q[j].x;
            if(q[j].op == 1)
            {
                if(l <= blk.l && r >= blk.r) blk.totalchange(x);
                else blk.partchange(max(l, blk.l), min(r, blk.r), x);
            }
            else
            {
                if(l <= blk.l && r >= blk.r) ans[j] += blk.totalquery(x);
                else ans[j] += blk.partquery(max(l, blk.l), min(r, blk.r), x);
            }
        }
        blk.destroy();
    }

    for(int i = 1; i <= m; i ++ )
        if(q[i].op == 2)
            printf("%d\n", ans[i]);

    return 0;
}
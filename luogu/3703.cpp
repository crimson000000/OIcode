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

const int N = 1e6 + 10;
int n, m;
int h[N], e[N], ne[N], idx;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

namespace sp
{
    int fa[N], siz[N], dep[N], son[N];
    inline void dfs1(int u, int f)
    {
        fa[u] = f, dep[u] = dep[f] + 1;
        siz[u] = 1;
        int maxsiz = -1;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == f) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if(siz[v] > maxsiz)
            {
                maxsiz = siz[v];
                son[u] = v;
            }
        }
    }

    int top[N], L[N], R[N], anti[N], tim;
    inline void dfs2(int u, int t)
    {
        top[u] = t;
        L[u] = ++ tim;
        anti[tim] = u;
        if(!son[u]) 
        {
            R[u] = tim;
            return;
        }
        dfs2(son[u], t);
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }

        R[u] = tim;
    }

    struct seg
    {
        int l, r;
        int val, add;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].val = max(t[p << 1].val, t[p << 1 | 1].val);
    }

    inline void pushdown(int p)
    {
        if(t[p].add)
        {
            t[p << 1].val += t[p].add;
            t[p << 1 | 1].val += t[p].add;
            t[p << 1].add += t[p].add;
            t[p << 1 | 1].add += t[p].add;
            t[p].add = 0;
        }
    }

    inline void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r)
        {
            t[p].val = dep[anti[l]];
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void change(int p, int l, int r, int v)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            t[p].val += v;
            t[p].add += v;
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) change(p << 1, l, r, v);
        if(r > mid) change(p << 1 | 1, l, r, v);
        pushup(p);
    }

    inline int query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].val;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        int res = -0x3f3f3f3f;
        if(l <= mid) res = max(res, query(p << 1, l, r));
        if(r > mid) res = max(res, query(p << 1 | 1, l, r));
        return res;
    }
}

using sp::L;
using sp::R;
using sp::top;
using sp::fa;
using sp::dep;

namespace LCT
{
    struct node
    {
        int fa, ch[2];
        bool rev;
    }t[N];

    inline void reverse(int p)
    {
        swap(t[p].ch[0], t[p].ch[1]);
        t[p].rev ^= 1;
    }
    
    inline bool ident(int p, int fa)
    {
        return t[fa].ch[1] == p;
    }

    inline void connect(int p, int fa, int s)
    {
        t[p].fa = fa;
        t[fa].ch[s] = p;
    }

    inline bool is_root(int p)
    {
        return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
    }

    inline void pushdown(int p)
    {
        if(t[p].rev)
        {
            if(t[p].ch[0]) reverse(t[p].ch[0]);
            if(t[p].ch[1]) reverse(t[p].ch[1]);
            t[p].rev = 0;
        }
    }

    inline void pushdown_all(int p)
    {
        if(!is_root(p)) pushdown_all(t[p].fa);
        pushdown(p);
    }

    inline void rotate(int p)
    {
        int f = t[p].fa, ff = t[f].fa, k = ident(p, f);
        connect(t[p].ch[k ^ 1], f, k);
        t[p].fa = ff;
        if(!is_root(f)) t[ff].ch[ident(f, ff)] = p;
        connect(f, p, k ^ 1);
    }

    inline void spaly(int p)
    {
        pushdown_all(p);
        while(!is_root(p))
        {
            int f = t[p].fa, ff = t[f].fa;
            if(!is_root(f))
                if(ident(p, f) ^ ident(f, ff))
                    rotate(p);
                else rotate(f);
            rotate(p);
        }
    }

    inline int find_root(int p)
    {
        while(t[p].ch[0]) p = t[p].ch[0];
        return p;
    }

    inline void access(int x)
    {
        for(int y = 0; x; x = t[x].fa)
        {
            spaly(x);
            int son;
            if(t[x].ch[1]) 
            {
                son = find_root(t[x].ch[1]);
                sp::change(1, L[son], R[son], 1);
            }
            if(t[x].ch[1] = y) 
            {
                son = find_root(y);
                sp::change(1, L[son], R[son], -1);
                // cout << son << ' ' << sp::query(1, L[4], L[4]) << endl;
            }
            t[x].ch[1] = y;
            y = x;
        }
    }
}

inline int lca(int x, int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    sp::dfs1(1, 0);
    sp::dfs2(1, 1);
    sp::build(1, 1, n);

    // cout << L[4] << ' ' << R[4] << endl;

    for(int i = 2; i <= n; i ++ )
        LCT::t[i].fa = fa[i];

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int x = read();
            LCT::access(x);
        }
        else if(op == 2)
        {
            int x = read(), y = read();
            int d1 = sp::query(1, L[x], L[x]);
            int d2 = sp::query(1, L[y], L[y]);
            int lc = lca(x, y);
            int d3 = sp::query(1, L[lc], L[lc]);
            printf("%d\n", d1 + d2 - (d3 << 1) + 1);
        }
        else
        {
            int x = read();
            printf("%d\n", sp::query(1, L[x], R[x]));
        }
        
        // for(int i = 1; i <= n; i ++ )
        //     cout << sp::query(1, L[i], L[i]) << ' ';
        // puts("");
    }

    return 0;
}

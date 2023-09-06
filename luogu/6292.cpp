#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
int n, m;
int pos[N];
char s[N];

struct qu
{
    int l, r, id;
    bool operator < (const qu& x) const
    {
        return r < x.r;
    }
}q[N];
ll ans[N];

struct SuffixAM
{
    int tr[N][26], link[N];
    int len[N];
    int lst, idx;

    void init()
    {
        link[0] = -1;
    }

    void insert(char ch)
    {
        int p = lst, cur = ++ idx, c = ch - 'a';
        len[cur] = len[p] + 1;
        while(p != -1 && !tr[p][c])
        {
            tr[p][c] = cur;
            p = link[p];
        }
        if(p == -1) link[cur] = 0;
        else
        {
            int q = tr[p][c];
            if(len[q] == len[p] + 1) link[cur] = q;
            else
            {
                int copy = ++ idx;
                link[copy] = link[q];
                len[copy] = len[p] + 1;
                for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
                while(p != -1 && tr[p][c] == q)
                {
                    tr[p][c] = copy;
                    p = link[p];
                }
                link[cur] = link[q] = copy;
            } 
        }
        lst = cur;
    }
}SAM;

struct segment
{
    struct seg
    {
        int l, r;
        ll sum, add;
    }t[N << 2];

    void pushup(int p)
    {
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    }

    void Add(int p, ll x)
    {
        t[p].sum += x * (t[p].r - t[p].l + 1);
        t[p].add += x;
    }

    void pushdown(int p)
    {
        if(t[p].add)
        {
            Add(p << 1, t[p].add);
            Add(p << 1 | 1, t[p].add);
            t[p].add = 0;
        }
    }
    
    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void change(int p, int l, int r, ll v)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            Add(p, v);
            return;
        }
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) change(p << 1, l, r, v);
        if(r > mid) change(p << 1 | 1, l, r, v);
        pushup(p);
    }

    ll query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r) return t[p].sum;
        pushdown(p);
        int mid = t[p].l + t[p].r >> 1;
        ll res = 0;
        if(l <= mid) res += query(p << 1, l, r);
        if(r > mid) res += query(p << 1 | 1, l, r);
        return res;
    }
}tree;

struct LinkCutTree
{
    struct node
    {
        int ch[2];
        int fa, val;
        int cov;
    }t[N];
    int cnt, rt;

    bool is_root(int p)
    {
        return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
    }

    bool ident(int p, int fa)
    {
        return t[fa].ch[1] == p;
    }

    void connect(int p, int fa, int s)
    {
        t[p].fa = fa;
        t[fa].ch[s] = p;
    }

    void tag(int p, int v)
    {
        t[p].val = v;
        t[p].cov = v;
    }

    void pushdown(int p)
    {
        if(t[p].cov)
        {
            if(t[p].ch[0]) tag(t[p].ch[0], t[p].cov);
            if(t[p].ch[1]) tag(t[p].ch[1], t[p].cov);
            t[p].cov = 0;
        }
    }

    void pushdown_all(int p)
    {
        if(!is_root(p)) pushdown_all(t[p].fa);
        pushdown(p);
    }

    void rotate(int p)
    {
        int f = t[p].fa, ff = t[f].fa, k = ident(p, f);
        connect(t[p].ch[k ^ 1], f, k);
        t[p].fa = ff;
        if(!is_root(f)) t[ff].ch[ident(f, ff)] = p;
        connect(f, p, k ^ 1);
    }

    void spaly(int p)
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

    void access(int x, int v)
    {
        int y;
        for(y = 0; x; x = t[x].fa)
        {
            spaly(x);
            t[x].ch[1] = y;
            if(t[x].val)
                tree.change(1, t[x].val - SAM.len[x] + 1, t[x].val - SAM.len[t[x].fa], -1);
            y = x;
        }
        tag(y, v);
        tree.change(1, 1, v, 1);
    }
}LCT;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    SAM.init();
    for(int i = 1; i <= n; i ++ ) SAM.insert(s[i]), pos[i] = SAM.lst;
    tree.build(1, 1, n);
    for(int i = 1; i <= SAM.idx; i ++ ) LCT.t[i].fa = SAM.link[i];

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        q[i].l = read(), q[i].r = read();
        q[i].id = i;
    }

    sort(q + 1, q + m + 1);
    for(int i = 1, r = 0; i <= m; i ++ )
    {
        while(r < q[i].r)
        {
            r ++;
            LCT.access(pos[r], r);
        }
        ans[q[i].id] = tree.query(1, q[i].l, q[i].r);
    }

    for(int i = 1; i <= m; i ++ ) printf("%lld\n", ans[i]);

    return 0;
}
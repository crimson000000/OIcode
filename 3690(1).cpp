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
struct lct
{
    int ch[2], fa;
    int siz, val, sum;
    bool rev;
}t[N];

inline void pushup(int p)
{
    t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1;
    t[p].sum = t[t[p].ch[0]].sum ^ t[p].val ^ t[t[p].ch[1]].sum;
}

inline void connect(int p, int fa, int s)
{
    t[fa].ch[s] = p;
    t[p].fa = fa;
}

inline bool is_root(int p)
{
    return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
}

inline bool ident(int p, int fa)
{
    return t[fa].ch[1] == p;
}

inline void reverse(int p)
{
    t[p].rev ^= 1;
    swap(t[p].ch[0], t[p].ch[1]);
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
    pushup(f), pushup(p);
}

inline void splay(int p)
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

inline void access(int x)
{
    for(int y = 0; x; x = t[x].fa)
    {
        splay(x);
        t[x].ch[1] = y;
        pushup(x);
        y = x;
    }
}

inline void make_root(int x)
{
    access(x);
    splay(x);
    reverse(x);
}

inline int find_root(int x)
{
    access(x);
    splay(x);
    int p = x;
    while(t[p].ch[0]) 
    {
        pushdown(p);
        p = t[p].ch[0];
    }
    splay(p);
    return p;
}

inline void link(int x, int y)
{
    make_root(x);
    if(find_root(y) == x) return;
    t[x].fa = y;
}

inline void cut(int x, int y)
{
    make_root(x);
    if(find_root(y) != x || t[y].ch[0] || t[y].fa != x) return;
    t[y].fa = t[x].ch[1] = 0;
    pushup(x);
}

inline void split(int x, int y)
{
    make_root(x);
    access(y);
    splay(y);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        t[i].val = read();
        t[i].sum = t[i].val;
        t[i].siz = 1;
    }

    while(m -- )
    {
        int op = read() + 1, x = read(), y = read();
        if(op == 1)
        {
            split(x, y);
            printf("%d\n", t[y].sum);
        }
        else if(op == 2)
        {
            link(x, y);
        }
        else if(op == 3)
        {
            cut(x, y);
        }
        else
        {
            splay(x);
            t[x].val = y;
            pushup(x);
        }
    }

    return 0;
}
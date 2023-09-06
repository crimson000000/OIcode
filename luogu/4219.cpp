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
struct node
{
    int siz, siz2;
    int ch[2], fa;
    bool rev;
}t[N];

int n, q;

inline void pushup(int p)
{
    t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1 + t[p].siz2;
}

inline bool is_root(int p)
{
    return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
}

inline void connect(int p, int fa, int s)
{
    t[p].fa = fa;
    t[fa].ch[s] = p;
}

inline bool ident(int p, int fa)
{
    return t[fa].ch[1] == p;
}

inline void reverse(int p)
{
    swap(t[p].ch[0], t[p].ch[1]);
    t[p].rev ^= 1;
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

inline void access(int x)
{
    for(int y = 0; x; x = t[x].fa)
    {
        spaly(x);
        t[x].siz2 += t[t[x].ch[1]].siz - t[y].siz;
        t[x].ch[1] = y;
        pushup(x);
        y = x;
    }
}

inline void make_root(int x)
{
    access(x);
    spaly(x);
    reverse(x);
}

inline void link(int x, int y)
{
    make_root(x);
    make_root(y);
    t[y].siz2 += t[x].siz;
    t[x].fa = y;
}

inline void cut(int x, int y)
{
    make_root(x);
    access(y);
    spaly(y);
    t[y].ch[0] = t[x].fa = 0;
    pushup(x);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif
    
    n = read(), q = read();
    for(int i = 1; i <= n; i ++ )
    {
        t[i].siz = 1;
    }

    while(q -- )
    {
        char op[10];
        scanf("%s", op);
        int x = read(), y = read();
        if(op[0] == 'A')
        {
            link(x, y);
        }
        else
        {
            cut(x, y);
            make_root(x);
            make_root(y);
            printf("%lld\n", (ll)t[x].siz * t[y].siz);
            link(x, y);
        }
    }

    return 0;
}

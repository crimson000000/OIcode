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

const int N = 1e5 + 10;
ld fact[N];
struct fun
{
    int type;
    ld a, b;
};

struct node
{
    int ch[2], fa;
    ld a[30], val[30];
    bool rev;
}t[N];

inline void fuck(node& a)
{
    int type = read();
    ld x, y;
    scanf("%lf%lf", &x, &y);
    for(int i = 0; i <= 20; i ++ ) a.val[i] = 0;
    if(type == 1)
    {
        ld k = 1, S = sin(y), C = cos(y);
        for(int i = 0; i <= 20; i ++ )
        {
            if(i % 4 == 0) a.val[i] += k * S;
            if(i % 4 == 1) a.val[i] += k * C;
            if(i % 4 == 2) a.val[i] -= k * S;
            if(i % 4 == 3) a.val[i] -= k * C;
            k = x * k;
        }
    }
    else if(type == 2)
    {
        ld k = 1, E = exp(y);
        for(int i = 0; i <= 20; i ++ )
        {
            a.val[i] += E * k;
            k = x * k;
        }
    }
    else
    {
        a.val[0] = y;
        a.val[1] = x;
        for(int i = 2; i <= 20; i ++ ) a.val[i] = 0; 
    }
}

inline void pushup(int p)
{
    for(int i = 0; i < 21; i ++ ) 
        t[p].a[i] = t[t[p].ch[0]].a[i] + t[t[p].ch[1]].a[i] + t[p].val[i];
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

inline bool is_root(int p)
{
    return !(t[t[p].fa].ch[0] == p || t[t[p].fa].ch[1] == p);
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

inline int find_root(int x)
{
    access(x);
    spaly(x);
    int p = x;
    while(t[p].ch[0])
    {
        pushdown(p);
        p = t[p].ch[0];
    }
    spaly(p);
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
    if(find_root(y) != x || t[y].fa != x || t[y].ch[1]) return;
    t[y].fa = t[x].ch[1] = 0;
    pushup(x);
}

inline void split(int x, int y)
{
    make_root(x);
    access(y);
    spaly(y);
}

int n, m, type;

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();
    char type[10];
    scanf("%s", type);

    fact[0] = 1;
    for(int i = 1; i <= 20; i ++ ) fact[i] = fact[i - 1] * i;

    for(int i = 1; i <= n; i ++ )
    {
        fuck(t[i]);
    }

    while(m -- )
    {
        char op[20];
        scanf("%s", op);
        if(op[0] == 'a')
        {
            int x = read() + 1, y = read() + 1;
            link(x, y);
        }
        else if(op[0] == 'd')
        {
            int x = read() + 1, y = read() + 1;
            cut(x, y);
        }
        else if(op[0] == 'm')
        {
            int c = read() + 1;
            spaly(c);
            fuck(t[c]);
            pushup(c);
        }
        else
        {
            int u = read() + 1, v = read() + 1;
            ld x;
            scanf("%lf", &x);
            if(find_root(u) != find_root(v)) 
            {
                puts("unreachable");
                continue;
            }

            split(u, v);

            ld res = 0, xx = 1;
            for(int i = 0; i < 21; i ++ )
            {
                res += t[v].a[i] * xx / fact[i];
                xx *= x;
            }

            printf("%.10lf\n", res);
        }
    }

    return 0;
}

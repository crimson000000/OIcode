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

const int N = 4e5 + 10;
struct node 
{
    int fa, ch[2], val, sum;
    bool rev;
}t[N];
int n;
int p[N];

inline void pushup(int p)
{
    t[p].sum = t[t[p].ch[0]].sum + t[p].val + t[t[p].ch[1]].sum;
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
        t[p].rev = false;
    }
}

void pushdown_all(int p)
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
    while(t[x].ch[0])
    {
        pushdown(x);
        x = t[x].ch[0];
    }
    splay(x);
    return x;
}

inline void link(int x, int y)
{
    make_root(x);
    if(find_root(y) == x)
    {
        puts("no");
        return;
    }
    t[x].fa = y;
    puts("yes");
}

inline void split(int x, int y)
{
    make_root(x);
    access(y);
    splay(y);
}

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        t[i].val = read();
        t[i].sum = t[i].val;
        p[i] = i;
    }

    int q = read();

    while(q -- )
    {
        char op[20];
        scanf("%s", op);
        int x = read(), y = read();
        if(op[0] == 'b')
        {
            link(x, y);
            p[find(x)] = find(y);
        }
        else if(op[0] == 'p')
        {
            splay(x);
            t[x].val = y;
            pushup(x);
        }
        else
        {
            if(find(x) != find(y))
                puts("impossible");
            else
            {
                split(x, y);
                cout << t[y].sum << endl;
            }
        }
    }
    
    return 0;
}

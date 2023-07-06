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

const int N = 2e5 + 10, mod = 51061;
struct node
{
    int fa, ch[2], val, sum, siz;
    int add, mul;
    bool rev;
}t[N];
int n, q;

inline void pushup(int p)
{
    t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1;
    t[p].sum = (t[t[p].ch[0]].sum + t[t[p].ch[1]].sum + t[p].val) % mod;
}

inline void reverse(int p)
{
    t[p].rev ^= 1;
    swap(t[p].ch[0], t[p].ch[1]);
}

inline void eval(int p, int mul, int add)
{
    t[p].val = ((ll)t[p].val * mul + add) % mod;
    t[p].sum = ((ll)t[p].sum * mul % mod + t[p].siz * add % mod) % mod;
    t[p].mul = (ll)t[p].mul * mul % mod;
    t[p].add = ((ll)t[p].add * mul + add) % mod;
}

inline void pushdown(int p)
{
    if(t[p].ch[0]) eval(t[p].ch[0], t[p].mul, t[p].add);
    if(t[p].ch[1]) eval(t[p].ch[1], t[p].mul, t[p].add);
    t[p].mul = 1, t[p].add = 0;
    if(t[p].rev)
    {
        if(t[p].ch[0]) reverse(t[p].ch[0]);
        if(t[p].ch[1]) reverse(t[p].ch[1]);
        t[p].rev = false;
    }
}

inline bool is_root(int x)
{
    return !(t[t[x].fa].ch[1] == x || t[t[x].fa].ch[0] == x);
}

void pushdown_all(int p)
{
    if(!is_root(p)) pushdown_all(t[p].fa);
    pushdown(p);
}

inline bool ident(int p, int fa)
{
    return t[fa].ch[1] == p;
}

inline void connect(int p, int fa, int s)
{
    t[fa].ch[s] = p;
    t[p].fa = fa;
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

inline void make_root(int p)
{
    access(p);
    splay(p);
    reverse(p);
}

inline int find_root(int p)
{
    access(p);
    splay(p);
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
    t[x].ch[1] = t[y].fa = 0;
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

    n = read(), q = read();
    for(int i = 1; i <= n; i ++ )
    {
        t[i].mul = 1;
        t[i].siz = 1;
        t[i].val = 1;
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        link(a, b);
    }

    while(q -- )
    {
        char op[2];
        scanf("%s", op);
        if(op[0] == '+')
        {
            int x = read(), y = read(), c = read();
            split(x, y);
            eval(y, 1, c);
        }
        else if(op[0] == '-')
        {
            int x1 = read(), y1 = read(), x2 = read(), y2 = read();
            
            cut(x1, y1);
            link(x2, y2);
        }
        else if(op[0] == '*')
        {
            int x = read(), y = read(), c = read();
            split(x, y);
            eval(y, c, 0);
        }
        else
        {
            int x = read(), y = read();
            split(x, y);
            cout << t[y].sum << endl;
        }
        // cout << "yeah" << endl;
    }

    // for(int i = 1; i <= n; i ++ )
    // {
    //     pushdown_all(i);
    //     cout << t[i].val << ' ' << t[i].sum << ' ';
    //     cout << t[i].mul << ' ' << t[i].add << endl;
    // }
    
    return 0;
}

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

const int N = 1e5 + 10;
struct node
{
    int val, ch[2], fa, siz;
}t[N];
int root, cnt, n;

inline int New(int val, int fa)
{
    t[++ cnt].val = val;
    t[cnt].fa = fa;
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1;
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
    connect(p, ff, ident(f, ff));
    connect(f, p, k ^ 1);
    pushup(f), pushup(p);
}

inline void splay(int p, int top = 0)
{
    if(!top)
        root = p;
    while(t[p].fa != top)
    {
        int f = t[p].fa, ff = t[f].fa;
        if(ff != top)
            if(ident(p, f) ^ ident(f, ff))
                rotate(p);
            else rotate(f);
        rotate(p);
    }
}

void insert(int val, int &p = root, int fa = 0)
{
    if(!p)
        p = New(val, fa), splay(p);
    else if(t[p].val > val)
        insert(val, t[p].ch[0], p);
    else insert(val, t[p].ch[1], p);
}

void del_node(int p)
{
    splay(p);
    if(t[p].ch[1])
    {
        int now = t[p].ch[1];
        while(t[now].ch[0])
            now = t[now].ch[0];
        splay(now, p);
        connect(t[p].ch[0], now, 0);
        root = now;
        t[now].fa = 0;
        pushup(now);
    }
    else
        root = t[p].ch[0], t[root].fa = 0;
}

void del(int val, int p = root)
{
    if(t[p].val == val)
        del_node(p);
    else if(t[p].val > val)
        del(val, t[p].ch[0]);
    else del(val, t[p].ch[1]);
}

int getrank(int val)
{
    int p = root, rk = 1, pre = 0;
    while(p)
    {
        if(t[p].val >= val)
        {
            pre = p;
            p = t[p].ch[0];
        }
        else
        {
            rk += t[t[p].ch[0]].siz + 1;
            p = t[p].ch[1];
        }
    }
    if(pre) splay(pre);
    return rk;
}

int getval(int rank)
{
    int p = root;
    while(p)
    {
        if(t[t[p].ch[0]].siz + 1 == rank)
        {
            splay(p);
            break;
        }
        else if(t[t[p].ch[0]].siz >= rank)
            p = t[p].ch[0];
        else
        {
            rank -= t[t[p].ch[0]].siz + 1;
            p = t[p].ch[1];
        }
    }
    return t[p].val;
}

int getpre(int val)
{
    return getval(getrank(val) - 1);
}

int getnext(int val)
{
    return getval(getrank(val + 1));
} 

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    while(n -- )
    {
        int op = read(), x = read();
        if(op == 1)
        {
            insert(x);
        }
        else if(op == 2)
        {
            del(x);
        }
        else if(op == 3)
        {
            cout << getrank(x) << endl;
        }
        else if(op == 4)
        {
            cout << getval(x) << endl;
        }
        else if(op == 5)
        {
            cout << getpre(x) << endl;
        }
        else
        {
            cout << getnext(x) << endl;
        }
    }
    
    return 0;
}

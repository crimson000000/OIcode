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
    int fa, ch[2], val, size;
}t[N];
int root, cnt;

inline void pushup(int p)
{
    t[p].size = t[t[p].ch[0]].size + t[t[p].ch[1]].size + 1;
}

inline int New(int val, int fa)
{
    t[++ cnt].fa = fa;
    t[cnt].val = val;
    t[cnt].size = 1;
    return cnt;
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

void del(int x)
{
    splay(x);
    if(t[x].ch[1])
    {
        int p = t[x].ch[1];
        while(t[p].ch[0])
            p = t[p].ch[0];
        splay(p, x);
        connect(t[x].ch[0], p, 0);
        root = p;
        t[p].fa = 0;
        pushup(p);
    }
    else 
        root = t[x].ch[0], t[root].fa = 0;
}

void insert(int val, int &p = root, int fa = 0)
{
    if(!p)
        p = New(val, fa), splay(p); 
    else if(t[p].val > val)
        insert(val, t[p].ch[0], p);
    else insert(val, t[p].ch[1], p);
}

void dele(int val, int p = root)
{
    if(val == t[p].val)
        del(p);
    else if(t[p].val > val)
        dele(val, t[p].ch[0]);
    else dele(val, t[p].ch[1]);
}

int getrank(int val)
{
    int p = root, rk = 1, pre = 0;
    while(p)
    {
        if(val <= t[p].val)
        {
            pre = p;
            p = t[p].ch[0];
        }
        else
        {
            rk += t[t[p].ch[0]].size + 1;
            p = t[p].ch[1];
        }
    }
    if(pre)
        splay(pre);
    return rk;
}

int getnum(int rk)
{
    int p = root;
    while(p)
    {
        if(t[t[p].ch[0]].size + 1 == rk)
        {
            splay(p);
            break;
        }
        else if(t[t[p].ch[0]].size >= rk)
            p = t[p].ch[0];
        else 
        {
            rk -= t[t[p].ch[0]].size + 1;
            p = t[p].ch[1];
        }
    }
    return t[p].val;
}

int getpre(int val)
{
    return getnum(getrank(val) - 1);
}

int getnxt(int val)
{
    return getnum(getrank(val + 1));
}

void ldr(int p)
{
    if(!p) return;
    ldr(t[p].ch[0]);
    cout << t[p].val << ' ';
    ldr(t[p].ch[1]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n;
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
            dele(x);
        }
        else if(op == 3)
        {
            cout << getrank(x) << endl;
        }
        else if(op == 4)
        {
            cout << getnum(x) << endl;
        }
        else if(op == 5)
        {
            cout << getpre(x) << endl;
        }
        else
        {
            cout << getnxt(x) << endl;
        }
        // cout << "now: ";
        // ldr(root);
        // puts("");
    }

    // cout << getnxt(1) << endl;
    
    return 0;
}

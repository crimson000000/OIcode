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

const int N = 1e5 + 10, INF = 2147483647;
struct node
{
    int fa, ch[2], val, size;
    bool rev;
}t[N];
int root, cnt;
int n, m;
int orig[N];

inline void pushup(int p)
{
    t[p].size = t[t[p].ch[0]].size + t[t[p].ch[1]].size + 1;
}

inline void pushdown(int p)
{
    if(t[p].rev)
    {
        t[p].rev = 0;
        t[t[p].ch[0]].rev ^= 1;
        t[t[p].ch[1]].rev ^= 1;
        swap(t[p].ch[0], t[p].ch[1]);
    }
}

int build(int l, int r, int fa)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    int p = ++ cnt;
    t[p].fa = fa;
    t[p].size = 1;
    t[p].val = orig[mid];
    t[p].ch[0] = build(l, mid - 1, p);
    t[p].ch[1] = build(mid + 1, r, p);
    pushup(p);
    return p;
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
    pushdown(f), pushdown(p);
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

inline int find(int x)
{
    int p = root;
    while(1)
    {
        pushdown(p);
        if(t[t[p].ch[0]].size >= x)
            p = t[p].ch[0];
        else
        {
            x -= t[t[p].ch[0]].size + 1;
            if(x == 0) return p;
            p = t[p].ch[1];
        }
    }
}

inline void reverse(int l, int r)
{
    l = find(l - 1), r = find(r + 1);
    splay(l), splay(r, l);
    int pos = t[root].ch[1];
    pos = t[pos].ch[0];
    t[pos].rev ^= 1;
}

void ldr(int p)
{
    pushdown(p);
    if(t[p].ch[0]) ldr(t[p].ch[0]);
    if(t[p].val != -INF && t[p].val != INF)
        cout << t[p].val << ' ';
    if(t[p].ch[1]) ldr(t[p].ch[1]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    orig[1] = -INF;
    orig[n + 2] = INF;
    for(int i = 2; i <= n + 1; i ++ )
        orig[i] = i - 1;
    
    root = build(1, n + 2, 0);

    while(m -- )
    {
        int l = read(), r = read();
        reverse(l + 1, r + 1);
    }

    ldr(root);
    
    return 0;
}

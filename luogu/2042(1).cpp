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

const int N = 5e5 + 10, INF = 1e9;
struct node
{
    int fa, ch[2], val, siz;
    int lmax, rmax, amax;
    bool rev, cov;
    int sum;
}t[N];
int stk[N], a[N], tt, root;
int n, m;

inline int New(int val, int fa)
{
    int cnt = stk[tt -- ];
    t[cnt].fa = fa;
    t[cnt].cov = false;
    t[cnt].rev = false;
    t[cnt].val = val;
    t[cnt].siz = 1;
    t[cnt].sum = t[cnt].amax = val;
    t[cnt].lmax = t[cnt].rmax = max(0, val);
    t[cnt].ch[0] = t[cnt].ch[1] = 0;
    return cnt;
}

inline void pushup(int p)
{
    if(!p) return;
    t[p].siz = t[t[p].ch[0]].siz + t[t[p].ch[1]].siz + 1;
    t[p].lmax = max(max(t[t[p].ch[0]].lmax, t[t[p].ch[0]].sum + t[p].val + t[t[p].ch[1]].lmax), 0);
    t[p].rmax = max(max(t[t[p].ch[1]].rmax, t[t[p].ch[1]].sum + t[p].val + t[t[p].ch[0]].rmax), 0);
    t[p].amax = max(max(t[t[p].ch[0]].amax, t[t[p].ch[1]].amax), t[t[p].ch[0]].rmax + t[p].val + t[t[p].ch[1]].lmax);
    t[p].sum = t[t[p].ch[0]].sum + t[t[p].ch[1]].sum + t[p].val;
}

// void pushup(int u)
// {
//     t[u].siz=t[t[u].ch[0]].siz+t[t[u].ch[1]].siz+1;
//     t[u].sum=t[t[u].ch[0]].sum+t[t[u].ch[1]].sum+t[u].val;
//     t[u].lmax=max(t[t[u].ch[0]].lmax,t[t[u].ch[0]].sum+t[u].val+t[t[u].ch[1]].lmax);
//     t[u].rmax=max(t[t[u].ch[1]].rmax,t[t[u].ch[1]].sum+t[u].val+t[t[u].ch[0]].rmax);
//     t[u].amax=max(t[t[u].ch[0]].rmax+t[u].val+t[t[u].ch[1]].lmax,max(t[t[u].ch[0]].amax,t[t[u].ch[1]].amax));
// }

inline void cover(int x, int val)
{
    t[x].cov = true;
    t[x].val = val;
    t[x].sum = t[x].siz * val;
    t[x].lmax = t[x].rmax = max(0, t[x].sum);
    t[x].amax = max(t[x].sum, val);
}

inline void reverse(int x)
{
    if(!x) return; 
    swap(t[x].ch[0], t[x].ch[1]);
    swap(t[x].lmax, t[x].rmax);
    t[x].rev ^= 1;
}

inline void pushdown(int p)
{
    if(!p) return;
    if(t[p].cov)
    {
        t[p].rev = 0;
        if(t[p].ch[0]) cover(t[p].ch[0], t[p].val);
        if(t[p].ch[1]) cover(t[p].ch[1], t[p].val);
        t[p].cov = false;
    }
    if(t[p].rev)
    {
        if(t[p].ch[0]) reverse(t[p].ch[0]);
        if(t[p].ch[1]) reverse(t[p].ch[1]);
        t[p].rev = false;
    }
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

inline int find(int x)
{
    int p = root;
    while(p)
    {
        pushdown(p);
        if(t[t[p].ch[0]].siz >= x)
            p = t[p].ch[0];
        else if(x == t[t[p].ch[0]].siz + 1)
            return p;
        else
        {
            x -= t[t[p].ch[0]].siz + 1;
            if(!x) return p;
            p = t[p].ch[1];
        }
    }
}

void ldr(int p = root)
{
    pushdown(p); 
    if(t[p].ch[0])
        ldr(t[p].ch[0]);
    if(t[p].val == INF || t[p].val == INF) ;
    else cout << t[p].val << ' ';
    if(t[p].ch[1])
        ldr(t[p].ch[1]);
}

int get(int pos)
{
    return t[find(pos)].val;
}

int build(int l, int r, int fa)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    int p = New(a[mid], fa);
    t[p].ch[0] = build(l, mid - 1, p);
    t[p].ch[1] = build(mid + 1, r, p);
    pushup(p);
    return p;
}

inline void insert(int l, int n)
{
    for(int i = 0; i < n; i ++ )
        a[i] = read();

    // for(int i = 1; i <= n; i ++ )
    //     cout << a[i] << ' ';
    // puts("");
    int L = find(l), R = find(l + 1);
    
    splay(L);
    splay(R, L);
    int p = build(0, n - 1, R);
    t[R].ch[0] = p;
    pushup(R), pushup(L);
}

void del(int p)
{
    if(!p) return;
    stk[++ tt] = p;
    if(t[p].ch[0]) del(t[p].ch[0]);
    if(t[p].ch[1]) del(t[p].ch[1]);
}

void del(int l, int r)
{
    int L = find(l - 1), R = find(r + 1);
    splay(L);
    splay(R, L);
    del(t[R].ch[0]);
    t[R].ch[0] = 0;
    pushup(R), pushup(L);
}

inline void make_same(int l, int r, int val)
{
    int L = find(l - 1), R = find(r + 1);
    splay(L);
    splay(R, L);
    cover(t[R].ch[0], val);
    pushup(R), pushup(L);
}

inline void reverse(int l, int r)
{
    int L = find(l - 1), R = find(r + 1);
    splay(L);
    splay(R, L);
    reverse(t[R].ch[0]);
    pushup(R), pushup(L);
}

inline int sum(int l, int r)
{
    // cout << get(l - 1) << ' ' << get(r + 1) << endl;
    int L = find(l - 1), R = find(r + 1);
    splay(L);
    splay(R, L);
    return t[t[R].ch[0]].sum;
}

inline int max_sum()
{
    return t[root].amax;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= 500005; i ++ ) stk[++ tt] = i;
    t[0].amax = a[0] = a[n + 1] = -INF;
    for(int i = 1; i <= n; i ++ )
        a[i] = read();

    root = build(0, n + 1, 0);
    // cout << "yeah" << endl;

    // for(int i = 1; i <= n + 3; i ++ )
    // {
    //     cout << "yeah" << endl;
    //     printf("%d: %d\n", i, get(i));
    // }

    while(m -- )
    {
        char op[20];
        scanf("%s", op);
        if(op[0] == 'I')
        {
            int pos = read(), tot = read();
            insert(pos + 1, tot);
        }
        else if(op[0] == 'D')
        {
            int pos = read(), tot = read();
            del(pos + 1, pos + tot);
        }
        else if(op[0] == 'M' && op[2] == 'K')
        {
            int pos = read(), tot = read(), val = read();
            make_same(pos + 1, pos + tot, val);
        }
        else if(op[0] == 'R')
        {
            int pos = read(), tot = read();
            reverse(pos + 1, pos + tot);
        }
        else if(op[0] == 'G')
        {
            int pos = read(), tot = read();
            cout << sum(pos + 1, pos + tot) << endl;
        }
        else
        {
            cout << max_sum() << endl;
        }
        // cout << "yeah" << endl;
        // cout << "now:";
        // ldr();
        // puts("");
    }
    
    return 0;
}

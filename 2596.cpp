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
int n, m;
struct node
{
    int l, r;
    int siz, key, val;
    int fa;
}t[N];
int cnt, root;

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

inline int New(int val)
{
    t[++ cnt].siz = 1;
    t[cnt].key = rand();
    t[cnt].val = val;
    return cnt;
}

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        t[t[x].r].fa = x;
        pushup(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        t[t[y].l].fa = y;
        pushup(y);
        return y;
    }
}

inline void split(int p, int siz, int &x, int &y, int faa = 0, int fab = 0)
{
    if(!p) x = y = 0;
    else
    {
        if(t[t[p].l].siz + 1 > siz)
        {
            t[p].fa = fab;
            y = p;
            split(t[p].l, siz, x, t[y].l, faa, p);
        }
        else
        {
            t[p].fa = faa;
            x = p;
            split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y, p, fab);
        }
        pushup(p);
    }
}

#define x1 ____________xxxxxxxxxxxxxxxxxxxxxxx______________XxxxxxxxxxxXXXXXXxxxxxxxx1
#define y1 _____________yyyyyy________________Yyyyyyyyyyyyyyy______yyyyyyyyyyyyyyyy1
#define z1 ______________zzzzzzzz_______________________Zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz1
int x, y, z, x1, y1, z1;
inline void insert(int pos, int val)
{
    split(root, pos, x, y);
    root = merge(merge(x, New(val)), y);
}

inline int find(int x)
{
    int p = x, res = t[t[x].l].siz + 1;
    while(p != root && x)
    {
        if(t[t[p].fa].r == p) res += t[t[t[p].fa].l].siz + 1;
        p = t[p].fa;
    }
    return res;
}

inline void ldr(int p)
{
    if(!p) return;
    ldr(t[p].l);
    cout << t[p].val << ' ';
    ldr(t[p].r);
}

int a[N], pos[N];

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        root = merge(root, New(a[i]));
        pos[a[i]] = cnt;
    }

    while(m -- )
    {
        char op[20];
        scanf("%s", op);
        if(op[0] == 'T')
        {
            int s = read();
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(merge(y, x), z);
        }
        else if(op[0] == 'B')
        {
            int s = read();
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(merge(x, z), y);
        }
        else if(op[0] == 'I')
        {
            int s = read(), xx = read();
            int rk = find(pos[s]);
            split(root, rk - 1, x, y);
            split(y, 1, y, z);
            root = merge(x, z);
            split(root, rk + xx - 1, x1, y1);
            root = merge(merge(x1, y), y1);
        }
        else if(op[0] == 'A')
        {
            int s = read();
            int rk = find(pos[s]);
            printf("%d\n", rk - 1);
        }
        else
        {
            int s = read();
            split(root, s - 1, x, y);
            split(y, 1, y, z);
            printf("%d\n", t[y].val);
            root = merge(merge(x, y), z);
        }
        // ldr(root);
        // puts("");
    }

    return 0;
}
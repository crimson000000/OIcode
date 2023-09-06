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

const int N = 1e6 + 10;
int a[N];
struct fhq
{
    struct node
    {
        int l, r;
        int val, key;
        int lmax, rmax, maxn, sum;
        int siz;
    }t[N];
    int cnt, root;

    inline int New(int val)
    {
        t[++ cnt].val = val;
        t[cnt].key = rand();
        t[cnt].siz = 1;
        t[cnt].sum = val;
        t[cnt].lmax = t[cnt].rmax = max(0, val);
        t[cnt].maxn = val;
        return cnt;
    }

/*    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
        t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].val;
        t[p].lmax = max(t[t[p].l].lmax, t[p].sum + t[p].val + t[t[p].r].lmax);
        t[p].rmax = max(t[t[p].r].rmax, t[t[p].l].rmax + t[p].val + t[t[p].r].sum);
        t[p].maxn = max(max(t[t[p].l].maxn, t[t[p].r].maxn), t[t[p].l].rmax + t[p].val + t[t[p].r].lmax);
    }
*/

    inline void pushup(int p)
    {
        if(!p) return;
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
        t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].val;
        t[p].lmax = max(max(t[t[p].l].lmax, t[t[p].l].sum + t[p].val + t[t[p].r].lmax), 0);
        t[p].rmax = max(max(t[t[p].r].rmax, t[t[p].l].rmax + t[p].val + t[t[p].r].sum), 0);
        t[p].maxn = max(t[p].val, t[t[p].l].rmax + t[p].val + t[t[p].r].lmax);
        if(t[p].l) t[p].maxn = max(t[p].maxn, t[t[p].l].maxn);
        if(t[p].r) t[p].maxn = max(t[p].maxn, t[t[p].r].maxn);
    }
    
    int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key < t[y].key)
        {
            t[x].r = merge(t[x].r, y);
            pushup(x);
            return x;
        }
        else
        {
            t[y].l = merge(x, t[y].l);
            pushup(y);
            return y;
        }
    }

    void split(int p, int siz, int &x, int &y)
    {
        if(!p) x = y = 0;
        else
        {
            if(t[t[p].l].siz + 1 <= siz)
            {
                x = p;
                split(t[p].r, siz - t[t[p].l].siz - 1, t[x].r, y);
            }
            else
            {
                y = p;
                split(t[p].l, siz, x, t[y].l);
            }
            pushup(p);
        }
    }

    int x, y, z;
    int build(int l, int r)
    {
        if(l == r) return New(a[l]);
        int mid = l + r >> 1;
        int x = merge(build(l, mid), build(mid + 1, r));
        return x;
    }

    inline void insert(int p, int val)
    {
        split(root, p - 1, x, y);
        root = merge(merge(x, New(val)), y);
    }

    inline void del(int p)
    {
        split(root, p - 1, x, y);
        split(y, 1, y, z);
        root = merge(x, z);
    }

    inline void change(int p, int val)
    {
        split(root, p - 1, x, y);
        split(y, 1, y, z);
        root = merge(merge(x, New(val)), z);
    }

    inline void query(int l, int r)
    {
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);
        cout << t[y].maxn << endl;
        root = merge(merge(x, y), z); 
    }
} tree;

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();
    tree.root = tree.build(1, n);
    tree.t[0].maxn = -0x3f3f3f3f;

    m = read();
    while(m -- )
    {
        char op[5];
        scanf("%s", op);
        if(op[0] == 'I')
        {
            int p = read(), x = read();
            tree.insert(p, x);
        }
        else if(op[0] == 'D')
        {
            int p = read();
            tree.del(p);
        }
        else if(op[0] == 'R')
        {
            int p = read(), x = read();
            tree.change(p, x);
        }
        else
        {
            int p = read(), x = read();
            tree.query(p, x);
        }
    }
    
    return 0;
}

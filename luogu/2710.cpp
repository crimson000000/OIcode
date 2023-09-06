#define LOCAL
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f;
struct node
{
    int l, r, val;
    int key, size, sum, cov;
    int lmax, rmax, maxn;
    bool rev, cover;
}t[N];
int a[N], stk[N];
int root, cnt, len;
int n, m;

int New(int val)
{
    cnt = stk[len --];
    t[cnt].val = val;
    t[cnt].sum = t[cnt].maxn = val;
    t[cnt].key = rand();
    t[cnt].lmax = t[cnt].rmax = max(val, 0);
    t[cnt].size = 1;
    t[cnt].cover = t[cnt].cov = t[cnt].rev = t[cnt].l = t[cnt].r = 0;
    t[cnt].rev = 0;
    return cnt;
}

inline void pushup(int p)
{
    if(!p) return;
    t[p].size = t[t[p].l].size + t[t[p].r].size + 1;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].val;
    t[p].lmax = max(max(t[t[p].l].lmax, t[t[p].l].sum + t[p].val + t[t[p].r].lmax), 0);
    t[p].rmax = max(max(t[t[p].r].rmax, t[t[p].l].rmax + t[p].val + t[t[p].r].sum), 0);
    t[p].maxn = max(t[p].val, t[t[p].l].rmax + t[p].val + t[t[p].r].lmax);
    if(t[p].l) t[p].maxn = max(t[p].maxn, t[t[p].l].maxn);
    if(t[p].r) t[p].maxn = max(t[p].maxn, t[t[p].r].maxn);
}
void cover(int x, int c)
{
    t[x].val = t[x].cov = c;
    t[x].sum = t[x].size * c;
    t[x].lmax = max(0, t[x].sum);
    t[x].rmax = max(0, t[x].sum);
    t[x].maxn = max(c, t[x].sum);
    t[x].cover = true;
}

void reverse(int x)
{
    if(!x) return;
    swap(t[x].l, t[x].r);
    swap(t[x].lmax, t[x].rmax);
    t[x].rev ^= 1;
}

void pushdown(int p)
{
    if(!p) return;
    if(t[p].rev)
    {
        if(t[p].l) reverse(t[p].l);
        if(t[p].r) reverse(t[p].r);
        t[p].rev = 0;
    }
    if(t[p].cover)
    {
        if(t[p].l) cover(t[p].l, t[p].cov);
        if(t[p].r) cover(t[p].r, t[p].cov);
        t[p].cov = t[p].cover = 0;
    }
}

int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key > t[y].key)
    {
        pushdown(x);
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        pushdown(y);
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void split_size(int p, int sz, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        pushdown(p);
        if(t[t[p].l].size < sz)
        {
            x = p;
            split_size(t[p].r, sz - t[t[p].l].size - 1, t[p].r, y);
        }
        else
        {
            y = p;
            split_size(t[p].l, sz, x, t[p].l);
        }
        pushup(p);
    }
}

void ldr(int now)
{
    if(!now) return;
    pushdown(now);
    ldr(t[now].l);
    printf("%d ", t[now].val);
    ldr(t[now].r);
}

void del(int p)
{
    if(!p) return;
    stk[++ len] = p;
    if(t[p].l) del(t[p].l);
    if(t[p].r) del(t[p].r);
}

int build(int l, int r)
{
    if(l == r)
    {
        return New(a[l]);
    }
    int mid = l + r >> 1;
    int x = merge(build(l, mid), build(mid + 1, r));
    return x;
}

int x, y, z;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++ )
        scanf("%d", &a[i]);
    for(int i = 1; i <= 500000; i ++ ) stk[++ len] = i;
    
    root = merge(build(1, n), root);

    while(m -- )
    {
        char op[20];
        scanf("%s", op);
        if(op[0] == 'I')
        {
            int pos, tot;
            scanf("%d%d", &pos, &tot);
            for(int i = 1; i <= tot; i ++ ) scanf("%d", &a[i]);
            split_size(root, pos, x, y);
            x = merge(x, build(1, tot));
            root = merge(x, y);
        }
        else if (op[0] == 'D')
        {
            int pos, tot;
            scanf("%d%d", &pos, &tot);
            split_size(root, pos - 1, x, y);
            split_size(y, tot, y, z);
            del(y);
            root = merge(x, z);
        }
        else if(op[0] == 'R')
        {
            int pos, tot;
            scanf("%d%d", &pos, &tot);
            split_size(root, pos - 1, x, y);
            split_size(y, tot, y, z);
            reverse(y);
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'G' && op[3] == '-')
        {
            int pos, tot;
            scanf("%d%d", &pos, &tot);
            split_size(root, pos - 1, x, y);
            split_size(y, tot, y, z);
            cout << t[y].sum << endl;
            root = merge(merge(x, y), z);
            
        }
        else if(op[0] == 'M' && op[2] == 'X')
        {
            int pos, len;
            scanf("%d%d", &pos, &len);
            split_size(root, pos - 1, x, y);
            split_size(y, len, y, z);
            cout << t[y].maxn << endl;
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'M' && op[2] == 'K')
        {
            int pos, tot, cI;
            scanf("%d%d%d", &pos, &tot, &cI);
            split_size(root, pos - 1, x, y);
            split_size(y, tot, y, z);
            cover(y, cI);
            root = merge(merge(x, y), z);
        }
        else if(op[0] == 'G')
        {
            int pos;
            scanf("%d", &pos);
            split_size(root, pos - 1, x, y);
            split_size(y, 1, y, z);
            cout << t[y].val << endl;
            root = merge(merge(x, y), z);
        }
//        ldr(root);puts("");
    }
}
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
typedef long long ll;
struct node
{
    int l, r;
    ll val;
}t[N * 40];
int idx, root[N];
int n, m;

void pushup(int p)
{
    t[p].val = t[t[p].l].val + t[t[p].r].val;
}

void change(int l, int r, int &p, int x, int val)
{
    if(!p) p = ++ idx;
    t[p].val += val;
    if(l == r) return;
    int mid = l + r >> 1;
    if(x <= mid) change(l, mid, t[p].l, x, val);
    else change(mid + 1, r, t[p].r, x, val);
}

void merge(int &x, int y)
{
    if(!x || !y) x |= y;
    else
    {
        t[x].val += t[y].val;
        merge(t[x].l, t[y].l);
        merge(t[x].r, t[y].r);
    }
}

int split(int l, int r, int &k, int x, int y)
{
    int p = ++ idx;
    if(x <= l && y >= r)
    {
        t[p] = t[k];
        k = 0;
    }
    else
    {
        int mid = l + r >> 1;
        if(x <= mid) t[p].l = split(l, mid, t[k].l, x, y);
        if(y > mid) t[p].r = split(mid + 1, r, t[k].r, x, y);
        pushup(p);
        pushup(k);
    }
    return p;
}

ll query(int l, int r, int p, int x, int y)
{
    if(x <= l && r <= y) return t[p].val;
    int mid = l + r >> 1;
    ll sum = 0;
    if(x <= mid) sum += query(l, mid, t[p].l, x, y);
    if(y > mid) sum += query(mid + 1, r, t[p].r, x, y);
    return sum;
}

int query(int l, int r, int p, int kth)
{
    if(l == r) return l;
    int mid = l + r >> 1;
    if(kth <= t[t[p].l].val) return query(l, mid, t[p].l, kth);
    else return query(mid + 1, r, t[p].r, kth - t[t[p].l].val);
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for(int i = 1; i <= n; i ++ )
    {
        int x;
        scanf("%d", &x);
        change(1, n, root[1], i, x);
    }

    int last = 1;
    while(m -- )
    {
        int op, p, t1, x, y, q, k;
        scanf("%d%d", &op, &p);
        switch (op)
        {
        case 0:
            scanf("%d%d", &x, &y);
            root[++ last] = split(1, n, root[p], x, y);
            break;
        case 1:
            scanf("%d", &t1);
            merge(root[p], root[t1]);
            break;
        case 2:
            scanf("%d%d", &x, &q);
            change(1, n, root[p], q, x);
            break;
        case 3:
            scanf("%d%d", &x, &y);
            cout << query(1, n, root[p], x, y) << endl;
            break;
        case 4:
            scanf("%d", &k);
            if(k > t[root[p]].val) cout << -1 << endl;
            else cout << query(1, n, root[p], k) << endl;
            break;
        }
    }
    return 0;
}
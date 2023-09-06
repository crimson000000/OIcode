#define LOCAL
#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int N = 50010;
typedef long long ll;
typedef pair<int, int> PII;
int idx;

int read()
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

int a[N];
struct segment
{
    int l, r;
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> root;
}tr[N * 8];

void build(int p, int l, int r)
{
    tr[p].l = l, tr[p].r = r;
    for(int i = l; i <= r; i ++ )
        tr[p].root.insert(a[i]);
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void change(int p, int pos, int val)
{
    tr[p].root.erase(a[pos]);
    tr[p].root.insert(val);
    if(tr[p].l == tr[p].r) return;
    int mid = tr[p].l + tr[p].r >> 1;
    if(pos <= mid) change(p << 1, pos, val);
    else change(p << 1 | 1, pos, val);
}

int query_rank(int p, int l, int r, int val)
{
    if(tr[p].l >= l && tr[p].r <= r) 
        return tr[p].root.order_of_key(val);
    int mid = tr[p].l + tr[p].r >> 1;
    int rank = 0;
    if(l <= mid) rank += query_rank(p << 1, l, r, val);
    if(r > mid) rank += query_rank(p << 1 | 1, l, r, val);
    return rank;
}

int query_val(int l, int r, int rank)
{
    int le = 0, ri = 1e8;
    while(le < ri)
    {
        int mid = le + ri >> 1;
        if(query_rank(1, l, r, mid) > rank) ri = mid;
        else le = mid + 1;
    }
    return le;
}

int get_next(int p, int l, int r, int val)
{
    if(tr[p].l >= l && tr[p].r <= r)
        return getnxt(tr[p].root, val);
    int mid = tr[p].l + tr[p].r >> 1;
    int nxt = 0x3f3f3f3f;
    if(l <= mid) nxt = min(nxt, get_next(p << 1, l, r, val));
    if(r > mid) nxt = min(nxt, get_next(p << 1 | 1, l, r, val));
    return nxt;
}

int get_pre(int p, int l, int r, int val)
{
    if(tr[p].l >= l && tr[p].r <= r)
        return getpre(tr[p].root, val);
    int mid = tr[p].l + tr[p].r >> 1;
    int pre = -0x3f3f3f3f;
    if(l <= mid) pre = max(pre, get_pre(p << 1, l, r, val));
    if(r > mid) pre = max(pre, get_pre(p << 1 | 1, l, r, val));
    return pre;
}

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    build(1, 1, n);

    while(m -- )
    {
        int opt, l, r, k, pos;
        opt = read();
        switch(opt)
        {
            case 1:
                l = read(), r = read(), k = read();
                cout << query_rank(1, l, r, k) << endl;
                break;
            case 2:
                l = read(), r = read(), k = read();
                cout << query_val(l, r, k) << endl;
                break;
            case 3:
                pos = read(), k = read();
                change(1, pos, k);
                a[pos] = k;
                break;
            case 4:
                l = read(), r = read(), k = read();
                cout << get_pre(1, l, r, k) << endl;
                break;
            case 5:
                l = read(), r = read(), k = read();
                cout << get_next(1, l, r, k) << endl;
                break;
        }
    }
    return 0;
}

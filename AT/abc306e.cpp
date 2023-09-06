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

const int N = 1e6 + 10, M = 1e9 + 10;
struct node
{
    int l, r;
    ll sum, cnt;
}t[N << 4];
int root, cnt;
ll a[N];
int n, k, q;

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
}

void insert(int &p, int l, int r, int pos, int val)
{
    if(!p) p = ++ cnt;
    if(l == r)
    {
        t[p].cnt += val;
        t[p].sum = t[p].cnt * l;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, l, mid, pos, val);
    else insert(t[p].r, mid + 1, r, pos, val);
    pushup(p);
}

inline ll query(int p, int l, int r, int k)
{
    if(l == r)
    {
        if(t[p].cnt <= k) return t[p].sum;
        return l * k;
    }
    int mid = l + r >> 1;
    if(t[t[p].r].cnt >= k) return query(t[p].r, mid + 1, r, k);
    else return t[t[p].r].sum + query(t[p].l, l, mid, k - t[t[p].r].cnt);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), q = read();

    memset(a, -1, sizeof a);

    while(q -- )
    {
        int pos = read(), val = read();
        if(a[pos] != -1) insert(root, 0, M, a[pos], -1);
        a[pos] = val;
        insert(root, 0, M, val, 1);
        printf("%lld\n", query(root, 0, M, k));
    }

    return 0;
}

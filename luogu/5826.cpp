#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e5 + 10, M = 1e6 + 10;
int a[N], b[M];
int n, m, q;
int type;

struct node
{
    int l, r;
    int val;
}t[N * 200];
int root[N], cnt;

inline void insert(int &p, int q, int l, int r, int pos, int v)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r) 
    {
        t[p].val = v;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, t[q].l, l, mid, pos, v);
    else insert(t[p].r, t[q].r, mid + 1, r, pos, v);
}

inline int query(int p, int l, int r, int pos)
{
    if(!p) return -1;
    if(l == r) return t[p].val;
    int mid = l + r >> 1;
    if(pos <= mid) return query(t[p].l, l, mid, pos);
    else return query(t[p].r, mid + 1, r, pos);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    type = read(), n = read(), q = read(), m = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = n - 1; i >= 0; i -- )
    {
        insert(root[i], root[i + 1], 1, m, a[i + 1], i + 1);
    }

    // for(int i = 0; i <= n; i ++ )
    // {
    //     for(int j = 1; j <= m; j ++ )
    //         cout << query(root[i], 1, m, j) << ' ';
    //     puts("");
    // }

    while(q -- )
    {
        int tt = read();
        for(int i = 1; i <= tt; i ++ ) b[i] = read();
        int p = 0;
        bool flag = true;
        for(int i = 1; i <= tt; i ++ )
        {
            int nxt = query(root[p], 1, m, b[i]);
            // cout << nxt << endl;
            if(nxt == -1)
            {
                puts("No");
                flag = false;
                break;
            }
            p = nxt;
        }
        if(flag) puts("Yes");
    }

    return 0;
}
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
int a[N], pre[N], lst[N];
int n, m;

struct node
{
    int l, r;
    int cnt;
}t[N * 50];
int root[N], cnt;

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
}

inline void insert(int &p, int q, int l, int r, int pos)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].cnt ++;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, t[q].l, l, mid, pos);
    else insert(t[p].r, t[q].r, mid + 1, r, pos);
    pushup(p);
}

inline int query(int p, int q, int l, int r, int v)
{
    if(l > v) return 0;
    if(r <= v) return t[p].cnt - t[q].cnt;
    int mid = l + r >> 1;
    return query(t[p].l, t[q].l, l, mid, v) + 
            query(t[p].r, t[q].r, mid + 1, r, v);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ ) 
    {
        pre[i] = lst[a[i]];
        lst[a[i]] = i;
        insert(root[i], root[i - 1], 0, n, pre[i]);
        // cout << t[4].cnt << endl;
    }

    m = read();

    while(m -- )
    {
        int l = read(), r = read();
        printf("%d\n", query(root[r], root[l - 1], 0, n, l - 1));
    }

    return 0;
}

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

const int N = 1e6 + 10, M = 1e9;
int a[N];
int n, m;
struct seg
{
    int l, r;
    int sum;
}t[N * 10];
int root[N], cnt;

void pushup(int p)
{
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
}

void insert(int &p, int q, int l, int r, int pos, int v)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].sum += l * v;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, t[q].l, l, mid, pos, v);
    else insert(t[p].r, t[q].r, mid + 1, r, pos, v);
    pushup(p);
}

int query(int p, int l, int r, int L, int R)
{
    if(!p) return 0;
    if(l >= L && r <= R) return t[p].sum;
    int mid = l + r >> 1;
    int res = 0;
    if(L <= mid) res += query(t[p].l, l, mid, L, R);
    if(R > mid) res += query(t[p].r, mid + 1, r, L, R);
    return res;
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
        insert(root[i], root[i - 1], 1, M, a[i], 1);

    m = read();
    while(m -- )
    {
        int l = read(), r = read();
        int lst = 0, ans = 1;
        while(query(root[r], 1, M, lst + 1, ans) - query(root[l - 1], 1, M, lst + 1, ans))
        {
            int old_lst = lst;
            lst = ans;
            ans += query(root[r], 1, M, old_lst + 1, ans) - query(root[l - 1], 1, M, old_lst + 1, ans);
        }
        printf("%d\n", ans);
    }

    return 0;
}
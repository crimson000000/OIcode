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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int a[N];
int id[N];
int p[10];
int n, m;
int lastans;

struct Node
{
    int lmax, rmax, maxn, sum;
    Node() {lmax = rmax = maxn = sum = -INF;}
    Node(int v) {lmax = rmax = maxn = sum = v;}
};

Node merge(Node l, Node r)
{
    Node res;
    res.lmax = max(l.lmax, l.sum + r.lmax);
    res.rmax = max(r.rmax, r.sum + l.rmax);
    res.maxn = max(max(l.maxn, r.maxn), l.rmax + r.lmax);
    res.sum = l.sum + r.sum;
    return res;
}

struct seg
{
    int l, r;
    Node val;
}t[N * 20];
int root[N], cnt;

void pushup(int p)
{
    t[p].val = merge(t[t[p].l].val, t[t[p].r].val);
}

int build(int l, int r)
{
    int p = ++ cnt;
    if(l == r)
    {
        t[p].val = Node(1);
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = build(l, mid);
    t[p].r = build(mid + 1, r);
    pushup(p);
    return p;
}

void insert(int &p, int q, int l, int r, int pos, int v)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].val = Node(v);
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) insert(t[p].l, t[q].l, l, mid, pos, v);
    else insert(t[p].r, t[q].r, mid + 1, r, pos, v);
    pushup(p);
}

Node query(int p, int l, int r, int L, int R)
{
    if(L > R) return Node(0);
    if(l >= L && r <= R) return t[p].val;
    int mid = l + r >> 1;
    if(R <= mid) return query(t[p].l, l, mid, L, R);
    if(L > mid) return query(t[p].r, mid + 1, r, L, R);
    return merge(query(t[p].l, l, mid, L, R), query(t[p].r, mid + 1, r, L, R));
}

bool check(int mid)
{
    auto le = query(root[mid], 1, n, p[1], p[2]);
    auto ri = query(root[mid], 1, n, p[3], p[4]);
    auto sum = query(root[mid], 1, n, p[2] + 1, p[3] - 1);
    int maxn = le.rmax + sum.sum + ri.lmax;
    return maxn >= 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        id[i] = i;
    }

    sort(id + 1, id + n + 1, [](int x, int y){
        return a[x] < a[y];
    });

    root[1] = build(1, n);
    for(int i = 2; i <= n; i ++ ) 
        insert(root[i], root[i - 1], 1, n, id[i - 1], -1);

    // cout << query(root[2], 1, n, 2, 5).maxn << endl;
    
    m = read();

    while(m -- )
    {
        for(int i = 1; i <= 4; i ++ ) p[i] = (read() + lastans) % n + 1;
        sort(p + 1, p + 5);
        int l = 1, r = n, ans;
        while(l <= r)
        {
            int mid = l + r >> 1;
            if(check(mid)) l = mid + 1, ans = a[id[mid]];
            else r = mid - 1;
        }
        printf("%d\n", lastans = ans);
    }

    return 0;
}
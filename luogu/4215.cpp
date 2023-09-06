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

const int N = 1e5 + 10;
int n, m;
int a[N];
int num[N];
int ans;
int lastans;
struct node
{
    int l, r;
    int cnt;
    vector<int> a;
}t[N << 2];

void pushup(int p)
{
    t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
    if(!t[p].cnt)
    {
        for(auto x : t[p].a)
        {
            num[x] --;
            if(!num[x]) ans ++;
        }
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) 
    {
        t[p].cnt = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void cover(int p, int l, int r, int id)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].a.push_back(id);
        num[id] ++;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cover(p << 1, l, r, id);
    if(r > mid) cover(p << 1 | 1, l, r, id);
}

void change(int p, int pos)
{
    if(t[p].l == t[p].r)
    {
        t[p].cnt --;
        if(!t[p].cnt)
        {
            for(auto x : t[p].a)
            {
                num[x] --;
                if(!num[x]) ans ++;
            }
        }
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos);
    else change(p << 1 | 1, pos);
    pushup(p);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    
    build(1, 1, n);

    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        cover(1, l, r, i);
    }

    int q = read();
    while(q -- )
    {
        int x = read();
        x = (x + lastans - 1) % n + 1;
        change(1, x);
        printf("%d\n", lastans = ans);
    }

    return 0;
}
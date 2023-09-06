#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct node
{
    int id;
    ll val;

    bool operator < (const node & a) const
    {
        return val > a.val;
        // return id > a.id;
    }
};

priority_queue<node> q;
ll a[N], b[N];
ll ans, cnt;
int n, k;

struct seg
{
    int l, r;
    ll minn;
}t[N << 2];

inline void pushup(int p)
{
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].minn = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline int query(int p, int l, ll val)
{
    // cout << p << endl;
    if(l <= t[p].l)
    {
        if(t[p].minn > val) return 0;
        if(t[p].l == t[p].r) return t[p].l;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid)
    {
        int res = query(p << 1, l, val);
        if(res) return res;
    }
    return query(p << 1 | 1, l, val);
}

int stk[N], tt;
inline void dfs(int u, ll res)
{
    if(!res)
    {
        cnt --;
        if(!cnt)
        {
            cout << ans << endl;
            for(int i = 1; i <= tt; i ++ ) 
                printf("%d ", stk[i]);
            exit(0);
        }
    }

    for(int i = u + 1; i <= n; i ++ )
    {
        i = query(1, i, res);
        if(!i) return;
        stk[++ tt] = i;
        dfs(i, res - a[i]);
        tt --;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    k --;
    if(!k)
    {
        puts("0");
        return 0;
    }
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        b[i] = a[i];
    }

    sort(b + 1, b + n + 1);
    q.push({1, b[1]});
    while(k -- )
    {
        auto tmp = q.top();
        q.pop();
        if(tmp.val == ans) cnt ++;
        else ans = tmp.val, cnt = 1;
        if(tmp.id == n) continue;
        tmp.id ++;
        tmp.val += b[tmp.id];
        q.push(tmp);
        tmp.val -= b[tmp.id - 1];
        q.push(tmp);
    } 

    // printf("%lld\n", ans);
    
    build(1, 1, n);
    dfs(0, ans);

    return 0;
}

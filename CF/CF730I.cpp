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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, p, s;
ll ans;
int st[N];

struct node
{
    int val, id;
    bool operator < (const node& a) const
    {
        return val < a.val;
    }
}a[N], b[N];
inline bool cmp(node a, node b)
{
    return a.id < b.id;
}

priority_queue<node> q1, q2, q3; 

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), p = read(), s = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i].val = read();
        a[i].id = i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        b[i].val = read();
        b[i].id = i;
    }

    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    for(int i = 1; i <= p; i ++ )
    {
        ans += a[i].val;
        st[a[i].id] = 1;
    }

    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i ++ )
    {
        q1.push({a[i].val, i});
        q2.push({b[i].val, i});
        q3.push({b[i].val - a[i].val, i});
    }

    while(s -- )
    {
        int now = -INF;
        int opt, i, j;
        while(q2.size() && st[q2.top().id] != 0) q2.pop();
        if(q2.size())
        {
            if(q2.top().val > now)
            {
                now = q2.top().val;
                opt = 1;
                i = q2.top().id;
            }
        }
        while(q3.size() && st[q3.top().id] != 1) q3.pop();
        while(q1.size() && st[q1.top().id] != 0) q1.pop();
        if(q1.size() && q3.size())
        {
            ll sum = q1.top().val + q3.top().val;
            if(sum > now)
            {
                now = sum;
                opt = 2;
                i = q1.top().id;
                j = q3.top().id;
            }
        }
        ans += now;
        if(opt == 1)
        {
            st[i] = 2;
            q2.pop();
        }
        if(opt == 2)
        {
            st[i] = 1;
            st[j] = 2;
            q1.pop();
            q3.pop();
        }
    } 

    printf("%lld\n", ans);
    for(int i = 1; i <= n; i ++ ) 
        if(st[i] == 1)
            printf("%d ", i);
    puts("");
    for(int i = 1; i <= n; i ++ )
        if(st[i] == 2)
            printf("%d ", i);

    return 0;
}

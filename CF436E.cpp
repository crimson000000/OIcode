#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll a[N], b[N];
struct node
{
    ll val, id;
    bool operator < (const node t) const
    {
        return val > t.val;
    }
};
int n, m;
ll ans;
int type[N];

struct heap
{
    int op;
    priority_queue<node> q;
    inline void up()
    {
        while(q.size() && type[q.top().id] != op) q.pop();
    }

    inline void push(node a)
    {
        up();
        q.emplace(a);
    }

    inline void pop()
    {
        up();
        q.pop();
    }

    inline int size()
    {
        up();
        return q.size();
    }

    inline node top()
    {
        up();
        return q.top();
    }
}q1, q2, q3, q4, q5;

inline void push0(int p)
{
    type[p] = 0;
    q1.push({a[p], p});
    q4.push({b[p], p});
}

inline void push1(int p)
{
    type[p] = 1;
    q2.push({b[p] - a[p], p});
    q3.push({-a[p], p});
}

inline void push2(int p)
{
    type[p] = 2;
    q5.push({-b[p] + a[p], p});
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        a[i] = read(), b[i] = read();

    q1.op = q4.op = 0;
    q2.op = q3.op = 1;
    q5.op = 2;

    for(int i = 1; i <= n; i ++ )
        q1.push({a[i], i}), q4.push({b[i], i});

    for(int i = 1; i <= m; i ++ )
    {
        ll now = INF, opt = 0, id1, id2;
        if(q1.size() && now > q1.top().val)
        {
            now = q1.top().val;
            id1 = q1.top().id;
            opt = 1;
        }
        if(q2.size() && now > q2.top().val)
        {
            now = q2.top().val;
            id1 = q2.top().id;
            opt = 2;
        }
        if(q4.size() && q3.size() && now > (q3.top().val + q4.top().val))
        {
            now = q3.top().val + q4.top().val;
            id1 = q4.top().id;
            id2 = q3.top().id;
            opt = 3;
        }
        if(q5.size() && q4.size() && now > (q5.top().val + q4.top().val))
        {
            now = q5.top().val + q4.top().val;
            id1 = q5.top().id;
            id2 = q4.top().id;
            opt = 4;
        }

        ans += now;

        if(opt == 1) push1(id1);
        else if(opt == 2) push2(id1);
        else if(opt == 3) push0(id2), push2(id1);
        else push1(id1), push2(id2);
    }

    printf("%lld\n", ans);
    for(int i = 1; i <= n; i ++ )
        printf("%d", type[i]);

    return 0;
}

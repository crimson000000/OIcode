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

const int N = 3e6 + 10;
int n, m;

struct query
{
    int op, x, y, num;
    bool operator < (const query& a) const
    {
        if(x == a.x) return op < a.op;
        return x < a.x;
    }
}q[N << 3];
int tt;
int ans[N][4];

struct treearray
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int val)
    {
        for(; x <= N - 5; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;
vector<int> Y;

inline void dis()
{
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    for(int i = 1; i <= tt; i ++ )
        q[i].y = lower_bound(Y.begin(), Y.end(), q[i].y) - Y.begin() + 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        int x = read(), y = read(), z = read();
        q[++ tt] = {-1, x, y, z};
        Y.push_back(y);
    }
    
    for(int i = 1; i <= m; i ++ )
    {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        Y.push_back(y1 - 1), Y.push_back(y2);
        q[++ tt] = {i, x2, y2, 0};
        q[++ tt] = {i, x1 - 1, y2, 1};
        q[++ tt] = {i, x2, y1 - 1, 2};
        q[++ tt] = {i, x1 - 1, y1 - 1, 3};
    }

    dis();

    sort(q + 1, q + tt + 1);

    // for(int i = 1; i <= tt; i ++ )
    // {
    //     printf("%d %d %d\n", q[i].op, q[i].x, Y[q[i].y - 1]);
    // }

    for(int i = 1; i <= tt; i ++ )
    {
        if(q[i].op == -1)
        {
            bit.add(q[i].y, q[i].num);
        }
        else
        {
            ans[q[i].op][q[i].num] = bit.query(q[i].y);
        }
    }

    for(int i = 1; i <= m; i ++ )
    {
        printf("%d\n", ans[i][0] - ans[i][1] - ans[i][2] + ans[i][3]);
    }

    return 0;
}
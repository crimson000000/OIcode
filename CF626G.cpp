#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
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

const int N = 1e6 + 10;
const ld INF = 1e20, eps = 1e-10;
int n, t, q;
int p[N], l[N];
int c[N];
ld ans;

inline ld f(int x, int c)
{
    if(c == -1) return INF;
    if(c >= l[x]) return 0;
    return 1.0 * l[x] * p[x] / (c + l[x] + 1) / (c + l[x]);
}

inline ld g(int x)
{
    return 1.0 * p[x] * min(c[x], l[x]) / (min(c[x], l[x]) + l[x]);
}

struct node
{
    int x, c;
    ld val;
    node(int _x, int _c): x(_x), c(_c), val(f(_x, _c)) {}
    bool operator < (const node a) const
    {
        if(fabs(val - a.val) > eps) return val < a.val;
        return x < a.x;
    }
};

multiset<node> q1, q2;

inline void add()
{
    auto it = -- q1.end();
    ans += it -> val;
    int x = it -> x;
    q2.erase(node(x, c[x] - 1)), q2.insert(*it);
    q1.erase(*it), q1.insert(node(x, ++ c[x]));
}

inline void remove()
{
    auto it = q2.begin();
    ans -= it -> val;
    int x = it -> x;
    q1.erase(node(x, c[x])), q1.insert(*it);
    q2.erase(it), q2.insert(node(x, (-- c[x]) - 1));
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), t = read(), q = read();
    for(int i = 1; i <= n; i ++ ) p[i] = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        l[i] = read();
        q1.insert(node(i, 0));
        q2.insert(node(i, -1));
    }

    for(int i = 1; i <= t; i ++ )
        add();

    while(q -- )
    {
        int op = read(), x = read();
        q1.erase(node(x, c[x])), q2.erase(node(x, c[x] - 1));
        ans -= g(x);
        l[x] += (op == 1 ? 1 : -1);
        q1.insert(node(x, c[x])), q2.insert(node(x, c[x] - 1));
        ans += g(x);
        while((-- q1.end()) -> val > q2.begin() -> val + eps) remove(), add();
        printf("%.10Lf\n", ans);
    }

    return 0;
}

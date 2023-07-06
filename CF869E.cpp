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

const int N = 2510;
int n, m, q;
mt19937 rnd(time(0));

inline ll randd()
{
    return ((rnd() << 30) | rnd());
}

map<pair<PII, PII>, ll> mp;
struct treearray
{
    int c[N][N];
    #define lowbit(x) x & -x

    inline void add(int x, int y, int val)
    {
        for(int i = x; i <= n + 1; i += lowbit(i)) 
            for(int j = y; j <= m + 1; j += lowbit(j))
                c[i][j] += val;
    }

    inline int query(int x, int y)
    {
        int res = 0;
        for(int i = x; i; i -= lowbit(i))
            for(int j = y; j; j -= lowbit(j))
                res += c[i][j];
        return res;
    }

    inline void change(int x1, int y1, int x2, int y2, int val)
    {
        add(x2 + 1, y2 + 1, val);
        add(x1, y2 + 1, -val);
        add(x2 + 1, y1, -val);
        add(x1, y1, val);
    }
}t;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();

    while(q -- )
    {
        int op = read(), x1 = read(), y1 = read(), x2 = read(), y2 = read();
        x1 ++, x2 ++, y1 ++, y2 ++;
        if(op == 1)
        {
            ll x = randd();
            mp[{{x1, y1}, {x2, y2}}] = x;
            t.change(x1, y1, x2, y2, x);
        }
        else if(op == 2)
        {
            ll x = mp[{{x1, y1}, {x2, y2}}];
            t.change(x1, y1, x2, y2, -x);
        }
        else
        {
            ll q1 = t.query(x1, y1), q2 = t.query(x2, y2);
            if(q1 == q2) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}
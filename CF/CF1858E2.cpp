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

const int N = 1e6 + 10;
struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int v)
    {
        if(x == 0) return;
        for(; x <= N - 5; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;
int q, n;
int a[N];
set<int> t[N];

struct opt
{
    int p, v, len;
};
stack<opt> stk;

inline void change(int p, int x)
{
    int y = a[p];
    a[p] = x;
    if(x == y) return;
    if(!t[y].empty())
    {
        bit.add(*(t[y].begin()), -1);
        t[y].erase(p);
        if(t[y].size()) bit.add(*(t[y].begin()), 1);
    }   
    if(t[x].size()) bit.add(*(t[x].begin()), -1);
    t[x].insert(p);
    bit.add(*(t[x].begin()), 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    q = read();
    while(q -- )
    {
        char op[2];
        scanf("%s", op);
        if(op[0] == '+')
        {
            int x = read();
            stk.push({n + 1, a[n + 1], n});
            n ++;
            change(n, x);
        }
        else if(op[0] == '-')
        {
            int k = read();
            stk.push({n + 1, a[n + 1], n});
            n -= k;
        }
        else if(op[0] == '!')
        {
            auto t = stk.top();
            stk.pop();

            change(t.p, t.v);
            n = t.len;
        }
        else
        {
            cout << bit.query(n) << endl;
        }
    }

    return 0;
}
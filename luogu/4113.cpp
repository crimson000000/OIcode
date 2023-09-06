#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10;
int a[N], pre1[N], pre2[N];
int n, m, c;
vector<PII> qu[N];
int ans[N];

struct ta
{
    int c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), c = read(), m = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read();
        qu[r].emplace_back(l, i);
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(!pre1[a[i]]) pre1[a[i]] = i;
        else if(!pre2[a[i]]) 
            bit.add(pre1[a[i]], 1), 
            pre2[a[i]] = i;
        else
        {
            bit.add(pre1[a[i]], -1);
            bit.add(pre2[a[i]], 1);
            pre1[a[i]] = pre2[a[i]];
            pre2[a[i]] = i;
            
        }
        for(auto q : qu[i])
        {
            int id = q.second, l = q.first;
            ans[id] = bit.query(i) - bit.query(l - 1);
        }
    }

    for(int i = 1; i <= m; i ++ ) printf("%d\n", ans[i]);

    return 0;
}

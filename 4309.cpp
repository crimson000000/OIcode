#define LOCAL
#include <bits/stdc++.h>
#include<ext/rope>
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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int n;
struct ta
{
    int c[N];
    #define lowbit(x) x & -x

    inline void update(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] = max(c[x], val);
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res = max(res, c[x]);
        return res;
    }
}bit;

__gnu_cxx::rope<int> a;

int ans[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        int x = read();
        a.insert(x, i);
    }

    for(int i = 0; i < n; i ++ )
    {
        int t = a[i];
        bit.update(t, ans[t] = bit.query(t) + 1);
    }

    for(int i = 1; i <= n; i ++ )
    {
        printf("%d\n", ans[i] = max(ans[i], ans[i - 1]));
    }
    
    return 0;
}

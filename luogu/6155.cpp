#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
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
const int N = 1e6 + 10;
int a[N], b[N];
int tt;
stack<PII> stk;
int t[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();
    sort(a + 1, a + n + 1);

    for(int i = 1; i <= n; i ++ ) b[i] = read();

    int p = 1;
    for(int i = 1; 1; i ++ )
    {
        if(stk.empty())
        {
            if(p <= n)
                i = a[p];
            else break;
        }
        while(a[p] == i)
        {
            stk.push({a[p], p});
            p ++ ;
        }
        auto k = stk.top();
        stk.pop();
        t[k.second] = i - k.first;
    }

    sort(t + 1, t + n + 1);
    sort(b + 1, b + n + 1);
    reverse(b + 1, b + n + 1);
    ull ans = 0;
    for(int i = 1; i <= n; i ++ ) ans += (ull)b[i] * t[i];
    
    cout << ans << endl;
    
    return 0;
}

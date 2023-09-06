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

const int N = 1e6 + 10;
struct job
{
    ll tim, val;
    bool operator < (const job& a) const
    {
        return tim < a.tim;
    }
}a[N];
priority_queue<int, vector<int>, greater<int>> heap;
int n;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(register int i = 1; i <= n; i ++ )
    {
        a[i].tim = read(), a[i].val = read();
    }

    sort(a + 1, a + 1 + n);
    for(register int i = 1; i <= n; i ++ )
    {
        if(a[i].tim <= heap.size())
        {
            if(a[i].val > heap.top())
            {
                ans -= heap.top();
                heap.pop();
                heap.push(a[i].val);
                ans += a[i].val;
            }
        }
        else
        {
            heap.push(a[i].val);
            ans += a[i].val;
        }
    }

    cout << ans << endl;

    return 0;
}
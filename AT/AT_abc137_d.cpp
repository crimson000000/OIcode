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
    int time, val;
    bool operator < (const job& a) const
    {
        if(val != a.val) return val < a.val;
        return time > a.time;
    }
}a[N];

bool cmp(job a, job b)
{
    return a.time < b.time;
}

priority_queue<int> heap;
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        int time = read(), val = read();
        a[i] = {time, val};
    }

    sort(a + 1, a + 1 + n, cmp);

    ll ans = 0, cnt = 1;
    for(int t = 1; t <= m; t ++ )
    {
        while(a[cnt].time <= t && cnt <= n) heap.push(a[cnt].val), cnt ++;
        if(heap.empty()) continue;
        ans += heap.top();
        heap.pop();
    }

    cout << ans << endl;

    return 0;
}
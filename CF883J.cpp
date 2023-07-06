#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int long long

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
int a[N];
struct build
{
    int b, p;
    bool operator < (const build& a) const
    {
        return p > a.p;
    }
}b[N];
int sum[N];
int workday[N], maxn, tt, cnt;
int n, m, now, ans;

bool cmp(build a, build b)
{
    return a.b < b.b;
}

priority_queue<build> heap;
priority_queue<int> back;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= m; i ++ ) b[i].b = read();
    for(int i = 1; i <= m; i ++ ) b[i].p = read();

    for(int i = 1; i <= n; i ++ ) sum[i] = sum[i - 1] + a[i];

    for(int i = n; i >= 1; i -- )
    {
        if(a[i] > maxn) workday[++ tt] = i;
        maxn = max(maxn, a[i]);
    }

    sort(b + 1, b + m + 1, cmp);
    workday[tt + 1] = 0;

    cnt = m;
    back.push(0);

    for(int i = tt; i; i -- )
    {
        while(cnt && b[cnt].b > a[workday[i - 1]]) heap.push(b[cnt -- ]);

        now += sum[workday[i]] - sum[workday[i + 1]];

        while((heap.size() && back.size()) && ((heap.top().p <= now) || (heap.top().p < back.top())))
        {
            if(heap.top().b > a[workday[i]])
            {
                heap.pop();
                continue;
            } 

            if(heap.top().p > now && back.top())
            {
                now += back.top();
                back.pop();
                ans --;
            }

            ans ++;

            now -= heap.top().p;

            back.push(heap.top().p);

            heap.pop();
        }
    }

    cout << ans << endl;

    return 0;
}
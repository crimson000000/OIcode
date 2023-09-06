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
struct seg
{
    int l, r;
    bool operator < (const seg& a) const
    {
        if(l != a.l) return l < a.l;
        return r < a.r;
    }
}a[N], b[N];
int id1[N], id2[N];
int n, m1, m2;
int ans;

priority_queue<int, vector<int>, greater<int>> q1;
priority_queue<PII, vector<PII>, greater<PII>> q2;
int cnt1[N], cnt2[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m1 = read(), m2 = read();
    for(int i = 1; i <= m1; i ++ )
    {
        a[i].l = read();
        a[i].r = read();
    }

    for(int i = 1; i <= m2; i ++ )
    {
        b[i].l = read();
        b[i].r = read();
    }

    sort(a + 1, a + m1 + 1);
    sort(b + 1, b + m2 + 1);

    for(int i = 1; i <= m1; i ++ ) q1.push(i);
    for(int i = 1; i <= m1; i ++ )
    {
        while(q2.size() && q2.top().first < a[i].l) 
        {
            q1.push(q2.top().second);
            q2.pop();
        }
        id1[i] = q1.top();
        q1.pop();
        q2.push({a[i].r, id1[i]});
    }

    while(q1.size()) q1.pop();
    while(q2.size()) q2.pop();

    for(int i = 1; i <= m2; i ++ ) q1.push(i);
    for(int i = 1; i <= m2; i ++ )
    {
        while(q2.size() && q2.top().first < b[i].l) 
        {
            q1.push(q2.top().second);
            q2.pop();
        }
        id2[i] = q1.top();
        q1.pop();
        q2.push({b[i].r, id2[i]});
    }

    for(int i = 1; i <= m1; i ++ ) cnt1[id1[i]] ++;
    for(int i = 1; i <= m2; i ++ ) cnt2[id2[i]] ++;

    for(int i = 1; i <= n; i ++ ) cnt1[i] += cnt1[i - 1];
    for(int i = 1; i <= n; i ++ ) cnt2[i] += cnt2[i - 1];

    for(int x = 0; x <= n; x ++ )
        ans = max(ans, cnt1[x] + cnt2[n - x]);
    
    cout << ans << endl;

    return 0;
}

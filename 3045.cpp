#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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
priority_queue<ll, vector<ll>, greater<ll>> heap;
priority_queue<PII, vector<PII>, greater<PII>> q1, q2;
bitset<N> vis;
struct cow
{
    ll p, c;
    bool operator < (const cow& a) const
    {
        if(c != a.c) return c < a.c;
        return p < a.p;
    }
}a[N];
ll n, k, m;
ll ans, cnt;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read(), m = read();

    for(int i = 1; i <= n; i ++ )
    {
        ll p = read(), c = read();
        a[i] = {p, c};
    }

    sort(a + 1, a + n + 1);
    for(int i = 1; i <= k; i ++ )
    {
        if(ans + a[i].c <= m)
        {
            heap.emplace(a[i].p - a[i].c);
            ans += a[i].c;
            cnt ++;
        }
        else
        {
            cout << cnt << endl;
            return 0;
        }
    }

    if(k == n) 
    {
        cout << n << endl;
        return 0;
    }

    for(int i = k + 1; i <= n; i ++ )
    {
        q1.emplace(a[i].p, i);
        q2.emplace(a[i].c, i);
    }

    for(int i = k + 1; i <= n; i ++ )
    {
        while(vis[q1.top().second]) q1.pop();
        while(vis[q2.top().second]) q2.pop();
        int a1 = q1.top().first, a2 = q2.top().first;
        int p1 = q1.top().second, p2 = q2.top().second;
        if(a2 + heap.top() < a1)
        {
            vis[p2] = true;
            ans += a2 + heap.top();
            cnt ++;
            q2.pop(), heap.pop();
            heap.emplace(a[p2].p - a[p2].c);
        }
        else
        {
            vis[p1] = true;
            ans += a1;
            cnt ++;
            q1.pop();
        }
        
        if(ans > m)
        {
            cout << cnt - 1 << endl;
            return 0;
        }
    }

    cout << cnt << endl;

    return 0;
}
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
ll w[N];
ll n, k, ans, sec;
struct node
{
    ll val, dep;
    bool operator > (const node& a) const
    {
        if(val != a.val) return val > a.val;
        return dep > a.dep;
    }
};
priority_queue<node, vector<node>, greater<node>> heap;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) w[i] = read();

    while((n - 1) % (k - 1)) n ++;

    for(int i = 1; i <= n; i ++ ) heap.push({w[i], 0});
    while(heap.size() != 1)
    {
        ll res = 0, cnt = 0;
        for(int i = 1; i <= k; i ++ )
        {
            res += heap.top().val;
            cnt = max(cnt, heap.top().dep);
            heap.pop();
        }
        heap.push({res, cnt + 1});
        sec = max(sec, cnt + 1);
        ans += res;
    }

    cout << ans << endl;
    cout << sec << endl;

    return 0;
}
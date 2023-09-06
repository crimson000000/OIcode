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
ll a[N], b[N];
priority_queue<PII, vector<PII>, greater<PII>> heap;
int n, k;
ll res;

inline bool check(ll mid)
{
    res = 0;
    for(int i = 1; i <= n; i ++ )
    {
        heap.push({a[i], 0});
        if(b[i] - mid + heap.top().first < 0)
        {
            res += b[i] - mid + heap.top().first;
            heap.pop();
            heap.push({-b[i] + mid, 1});
        }
    }
    
    int cnt = 0;
    while(heap.size()) cnt += heap.top().second, heap.pop();
    return cnt <= k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ ) b[i] = read();

    ll l = -2e9, r = 2e9;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }

    check(l);

    cout << res + l * k << endl;

    return 0;
}
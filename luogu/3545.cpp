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
ll a[N], b[N];
priority_queue<PII> heap;
bool vis[N];
ll now;
int n;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ ) b[i] = read();
    
    for(int i = 1; i <= n; i ++ )
    {
        now += a[i];
        if(now < b[i] && !heap.empty() && b[i] < heap.top().first)
        {
            vis[heap.top().second] = false;
            now += heap.top().first;
            ans --;
            heap.pop();
        }
        if(now >= b[i])
        {
            vis[i] = true;
            now -= b[i];
            heap.emplace(b[i], i);
            ans ++;
        }
    }

    cout << ans << endl;
    for(int i = 1; i <= n; i ++ )
        if(vis[i])
            cout << i << ' ';

    

    return 0;
}
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
ll dist[N];
ll a[N];
int n;
ll l, r;

queue<int> q;
bitset<N> st;
void spaf()
{
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    st[0] = true;
    q.push(0);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;

        for(int i = 2; i <= n; i ++ )
        {
            int v = (u + a[i]) % a[1];
            if(dist[v] > dist[u] + a[i])
            {
                dist[v] = dist[u] + a[i];
                if(!st[v])
                {
                    q.push(v);
                    st[v] = true;
                }
            }
        }
    }
} 

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), l = read(), r = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    spaf();

    ll ans = 0;
    for(int i = 0; i < a[1]; i ++ )
    {
        // cout << dist[i] << endl; 
        if(dist[i] > r) continue;
        ll L = max(l, dist[i]);
        ll R = r;
        L = max(0ll, L - i);
        R = max(0ll, R - i);
        L = ceil(1.0 * L / a[1]);
        R = floor(1.0 * R / a[1]);
        // printf("-----%lld %lld\n", L, R);
        ans += (R - L) + 1;
        // cout << i << ' ' << (R - L) + 1 << endl;
    }

    cout << ans << endl;

    return 0;
}
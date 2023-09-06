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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
struct oil
{
    ll dist, y;
    bool operator < (const oil& a) const
    {
        return dist < a.dist;
    }
}e[N];
ll dist[N], price[N];
ll n, G, B, D;
ll nowB, nows;
ll ans;

ll findmin(ll s, ll lim)
{
    int now = s + 1, to = N - 1;
    while(now <= n)
    {
        if(dist[now] - dist[s] > lim) return to;
        if(price[now] < price[s]) return now;
        if(price[now] < price[to]) to = now;
        now ++;
    } 
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), G = read(), B = read(), D  = read();
    for(int i = 1; i <= n; i ++ )
    {
        e[i].dist = read(), e[i].y = read();
    }

    sort(e + 1, e + n + 1);
    for(int i = 1; i <= n; i ++ )
    {
        dist[i] = e[i].dist, price[i] = e[i].y;
        if(dist[i] - dist[i - 1] > G) 
        {
            puts("-1");
            return 0;
        }
    }

    if(dist[1] > B || D - dist[n] > G)
    {
        puts("-1");
        return 0;
    }

    price[N - 1] = INF;
    int now = 0, to;
    to = findmin(now, B);
    now = to;
    nowB = B - dist[to];

    if(dist[n] == D) price[n] = 0;
    else
    {
        n ++;
        dist[n] = D;
    } 

    while(now < n)
    {
        to = findmin(now, G);
        if(price[to] > price[now])
        {
            ans += (G - nowB) * price[now];
            nowB = G - dist[to] + dist[now];
        }
        else
        {
            ans += (dist[to] - dist[now] - nowB) * price[now];
            nowB = 0;
        }
        now = to;
    }

    cout << ans << endl;

    return 0;
}
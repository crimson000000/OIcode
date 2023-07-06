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
ll f[N], sum[N], h[N];
int q[N], hh, tt;
int n;

struct point
{
    ll x, y;
    int id;
    bool operator < (const point& a) const
    {
        if(x != a.x) return x < a.x;
        return y < a.y;
    }
}p[N], tmp[N];

inline ll Y(int i)
{
    return f[i] - sum[i] + h[i] * h[i];
}

void cdq(int l, int r)
{
    if(l == r) 
    {
        p[l].y = Y(l);
        return;
    }
    int mid = l + r >> 1;
    int x = l, y = mid + 1;
    for(int i = l; i <= r; i ++ )
        if(p[i].id <= mid) tmp[x ++ ] = p[i];
        else tmp[y ++ ] = p[i];
    
    for(int i = l; i <= r; i ++ ) p[i] = tmp[i];

    cdq(l, mid);

    hh = 1, tt = 0;
    for(int i = l; i <= mid; i ++ )
    {
        if(i > l && p[i].x == p[i - 1].x) continue;
        while(hh < tt && (p[q[tt]].y - p[q[tt - 1]].y) * (p[i].x - p[q[tt]].x) >=
                        (p[i].y - p[q[tt]].y) * (p[q[tt]].x - p[q[tt - 1]].x)) 
            tt --;
        q[++ tt] = i;
    }

    for(int i = mid + 1; i <= r; i ++ )
    {
        while(hh < tt && p[q[hh + 1]].y - p[q[hh]].y <= 2 * p[i].x * (p[q[hh + 1]].x - p[q[hh]].x))
            hh ++;
        int u = p[i].id, v = p[q[hh]].id;
        f[u] = min(f[u], f[v] + (h[u] - h[v]) * (h[u] - h[v]) + sum[u - 1] - sum[v]);
    }

    cdq(mid + 1, r);

    x = l, y = mid + 1;
    int now = l;
    while(x <= mid && y <= r)
    {
        if(p[x] < p[y]) tmp[now ++ ] = p[x ++ ];
        else tmp[now ++ ] = p[y ++ ]; 
    }
    while(x <= mid) tmp[now ++ ] = p[x ++ ];
    while(y <= r) tmp[now ++ ] = p[y ++ ];
    for(int i = l; i <= r; i ++ ) p[i] = tmp[i];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        h[i] = read();
        p[i].x = h[i];
        p[i].id = i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        int w = read();
        sum[i] = sum[i - 1] + w;
    }

    memset(f, 0x3f, sizeof f);
    f[1] = 0;
    sort(p + 1, p + n + 1);
    cdq(1, n);
    
    cout << f[n] << endl;

    return 0;
}
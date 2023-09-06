#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 1010;
int f[N], tmp[N][N];
int ans[N][N];
int n, m;

struct item
{
    int v[30], w[30], t;
}a[N];

inline void get(int id, int v, int w, int c)
{
    int cnt = 1;
    while(c)
    {
        a[id].t ++;
        if(c >= cnt)
        {
            c -= cnt;
            a[id].v[a[id].t] = v * cnt;
            a[id].w[a[id].t] = w * cnt;
        }
        else 
        {
            a[id].v[a[id].t] = v * c;
            a[id].w[a[id].t] = w * c;
            c = 0;
        }
        cnt <<= 1;
    }
}

inline void dp(int d, int x)
{
    for(int i = 1; i <= a[x].t; i ++ )
        for(int j = 1000; j >= 0; j -- )
            if(j >= a[x].v[i])
                f[j] = max(f[j], f[j - a[x].v[i]] + a[x].w[i]);
}

void cdq(int d, int l, int r)
{
    if(l == r)
    {
        memcpy(ans[l], f, sizeof f);
        return;
    }
    int mid = l + r >> 1;
    memcpy(tmp[d], f, sizeof f);
    for(int i = mid + 1; i <= r; i ++ ) dp(d, i);
    cdq(d + 1, l, mid);
    memcpy(f, tmp[d], sizeof f);
    for(int i = l; i <= mid; i ++ ) dp(d, i);
    cdq(d + 1, mid + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int v = read(), w = read(), c = read();
        get(i, v, w, c);
        // for(int j = 1; j <= a[i].t; j ++ )
        // {
        //     cout << a[i].v[j] << ' ' << a[i].w[j] << endl;
        // }
        // puts("");
    }

    cdq(1, 1, n);

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int d = read() + 1, e = read();
        printf("%d\n", ans[d][e]);
    }
    
    return 0;
}

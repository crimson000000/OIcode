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


const int N = 510, M = 1e4 + 10;
ll f[N][M];

struct po
{
    ll x, rest, w;
    bool operator < (const po &a) const
    {
        return x < a.x;
    }
}p[N];

ll e, n, k;
ll q[M * 10], hh, tt;

inline ll calc(int x, int k)
{
    return f[x - 1][k] + k * k * (p[x].x - p[x - 1].x) - k * p[x].w;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> k >> e >> n;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> p[i].x >> p[i].rest >> p[i].w;;
    }

    memset(f, 0x3f, sizeof f);
    sort(p + 1, p + n + 1);
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        hh = 1, tt = 0;
        for(int j = 0; j <= k; j ++ )
        {
            while(hh <= tt && calc(i, q[tt]) > calc(i, j)) tt --;
            while(hh <= tt && q[hh] < j - p[i].rest) hh ++;
            q[++ tt] = j;
            f[i][j] = calc(i, q[hh]) + j * p[i].w;
        }
    }

    cout << (f[n][k] + k * k * (e - p[n].x)) << endl;

    return 0;
}
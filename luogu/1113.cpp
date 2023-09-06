#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 100010;
int h[N], e[N], ne[N], idx;
int dist[N], v[N], din[N];
int q[N], hh = 0, tt = -1;
int n;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    din[b] ++;
}

void topsort()
{
    for(int i = 1; i <= n; i ++ )
        if(!din[i])
        {
            q[++ tt ] = i;
            dist[i] = v[i];
        }

    while(hh <= tt)
    {
        int t = q[hh ++ ]; 

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            din[j] --;
            if(!din[j]) q[++ tt] = j;
            dist[j] = max(dist[j], dist[t] + v[j]);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    scanf("%d", &n);

    for(int i = 1; i <= n; i ++ )
    {
        int ver, t;
        scanf("%d", &ver);
        scanf("%d", &v[ver]);
        while(cin >> t, t)
        {
            add(t, ver);
        }
    }

    topsort();

    int ans = 0;
    for(int i = 1; i <= n; i ++ )
        ans = max(ans, dist[i]);
    
    cout << ans << endl;
    
    return 0;
}

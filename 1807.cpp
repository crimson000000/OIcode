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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int q[N], hh, tt;
int n, m;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void spfa()
{
    hh = 0, tt = 0;
    q[tt ++ ] = 1;
    st[1] = true;
    
    while(hh != tt)
    {
        int t = q[hh ++ ];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if(!st[j])
                {
                    q[tt ++ ] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
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

    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    spfa();
    cout << (dist[n] == 0 ? -1 : dist[n]) << endl;

    return 0;
}

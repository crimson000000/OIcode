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

const int N = 3e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
int c[N];
int p[N];
int len;
int n, m, q;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int dp(int u, int fa)
{
    int dist = 0;
    int d1 = 0, d2 = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;

        int d = dp(j, u) + 1;
        dist = max(dist, d);
        if(d > d1) d2 = d1, d1 = d;
        else if(d > d2) d2 = d;
    }

    len = max(len, d1 + d2);
    return dist;
}

void getlen(int u)
{
    len = 0;
    dp(u, -1);
    c[u] = len;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read(), q = read();

    for(int i = 1; i <= n; i ++ ) p[i] = i;

    while(m -- )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        p[find(a)] = find(b);
    }

    for(int i = 1; i <= n; i ++ )
        if(p[i] == i)
            getlen(i);

    while(q -- )
    {
        int op = read(), x = read(), y;
        if(op == 1)
        {
            cout << c[find(x)] << endl;
        }
        else 
        {
            y = read();
            int fx = find(x), fy = find(y);
            if(fx == fy) continue;
            c[fx] = max((c[fx] + 1) / 2 + (c[fy] + 1) / 2 + 1, max(c[fx], c[fy]));
            p[fy] = fx;
        }
    }
    
    return 0;
}

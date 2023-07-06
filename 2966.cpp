#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
#define v(i) c[i].ver

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

const int N = 260;
int d[N][N];
int f[N][N];
int n, m, q;

struct po
{
    int val, ver;
    bool operator < (const po &W) const
    {
        return val < W.val;
    }
}c[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i ++ ) c[i] = {read(), i};

    sort(c + 1, c + 1 + n);

    memset(d, 0x3f, sizeof d);
    memset(f, 0x3f, sizeof f);
    while(m -- )
    {
        int a = read(), b = read(), c = read();
        d[a][b] = d[b][a] = min(d[a][b], c);
    }

    for(int i = 1; i <= n; i ++ ) d[i][i] = 0;

    for(int k = 1; k <= n; k ++ )
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= n; j ++ )
            {
                d[v(i)][v(j)] = min(d[v(i)][v(j)], d[v(i)][v(k)] + d[v(k)][v(j)]);
                f[v(i)][v(j)] = min(f[v(i)][v(j)], d[v(i)][v(j)] + max(c[i].val, max(c[k].val, c[j].val)));
            }
    
    while(m -- )
    {
        int a = read(), b = read();
        cout << f[a][b] << endl;
    }

    return 0;
}

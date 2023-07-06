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
int l[N], r[N], u[N], d[N], row[N], col[N], s[N], idx;
char g[100][100];
struct Op
{
    int x, y;
    char ch;
}op[N];
int ans[N], top;
int m = 16 * 16 * 4;

void init()
{
    for(int i = 0; i <= m; i ++ )
    {
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
        s[i] = 0;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void add(int &hh, int &tt, int x, int y)
{
    row[idx] = x, col[idx] = y, s[y] ++;
    l[tt] = idx, r[hh] = idx, r[idx] = tt, l[idx] = hh;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    tt = idx ++;
}

void remove(int p)
{
   r[l[p]] = r[p], l[r[p]] = l[p];
    for(int i = d[p]; i != p; i = d[i])
        for(int j = r[i]; j != i; j = r[j])
        {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}

void resume(int p)
{
    for(int i = u[p]; i != p; i = u[i])
        for(int j = l[i]; j != i; j = l[j])
        {
            s[col[j]] ++;
            u[d[j]] = j, d[u[j]] = j;
        }
    r[l[p]] = p, l[r[p]] = p;
} 

bool dfs()
{
    if(!r[0]) return true;
    int p = r[0];
    for(int i = r[0]; i; i = r[i])
        if(s[i] < s[p])
            p = i;
    remove(p);
    for(int i = d[p]; i != p; i = d[i])
    {
        ans[++ top] = row[i];
        for(int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if(dfs()) return true;
        for(int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top --;
    }
    resume(p);
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    int tot;
    tot = read();
    while(tot -- )
    {   
        init();
        for(int i = 0; i < 16; i ++ ) scanf("%s", g[i]);

        for(int i = 0, n = 1; i < 16; i ++ )
            for(int j = 0; j < 16; j ++ )
            {
                int a = 0, b = 15;
                if(g[i][j] != '-') a = b = g[i][j] - 'A';
                for(int k = a; k <= b; k ++, n ++ )
                {
                    int hh = idx, tt = idx;
                    op[n] = {i, j, k + 'A'};
                    add(hh, tt, n, i * 16 + j + 1);
                    add(hh, tt, n, 256 + i * 16 + k + 1);
                    add(hh, tt, n, 2 * 256 + j * 16 + k + 1);
                    add(hh, tt, n, 3 * 256 + (i / 4 * 4 + j / 4) * 16 + k + 1);
                }
            }

        dfs();

        for(int i = 1; i <= top; i ++ )
        {
            auto t = op[ans[i]];
            g[t.x][t.y] = t.ch;
        }
        for(int i = 0; i < 16; i ++ )
            puts(g[i]);

        puts("");
    }
    
    return 0;
}

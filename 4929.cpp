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

const int N = 10010;
int l[N], r[N], d[N], u[N], col[N], row[N], s[N];
int ans[N], top;
int idx;
int n, m;

inline void init()
{
    for(int i = 0; i <= m; i ++ )
    {
        l[i] = i - 1, r[i] = i + 1; 
        u[i] = i, d[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

inline void add(int &hh, int &tt, int x, int y)
{
    s[y] ++;
    col[idx] = y, row[idx] = x;
    l[idx] = hh, r[idx] = tt, r[hh] = idx, l[tt] = idx;
    u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
    tt = idx ++;
}

inline void remove(int p)
{
    l[r[p]] = l[p], r[l[p]] = r[p];
    for(int i = d[p]; i != p; i = d[i])
    {   
        for(int j = r[i]; j != i; j = r[j])
        {
            s[col[j]] --;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
    }
}

inline void resume(int p)
{
    for(int i = u[p]; i != p; i = u[i])
        for(int j = l[i]; j != i; j = l[j])
        {
            d[u[j]] = j, u[d[j]] = j;
            s[col[j]] ++;
        }
    l[r[p]] = p, r[l[p]] = p;
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

    n = read(), m = read();
    init();

    for(int i = 1; i <= n; i ++ )
    {
        int hh = idx, tt = idx;
        for(int j = 1; j <= m; j ++ )
        {
            int x = read();
            if(x) add(hh, tt, i, j);
        }
    }

    if(dfs())
    {
        for(int i = 1; i <= top; i ++ ) cout << ans[i] << ' ';
    }
    else puts("No Solution!");
    
    return 0;
}

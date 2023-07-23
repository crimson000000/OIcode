#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int ans[N], rec[30][N], sec[N];
int minn = 0x3f3f3f3f, nowans;
int n;
int a[N];

inline void dfs(int dep, int len)
{
    if(rec[dep][1] == 0 && len <= 1)
    {
        if(nowans < minn)
        {
            minn = nowans;
            for(int i = 1; i <= nowans; i ++ )
                ans[i] = sec[i];
        }
        return;
    }
    else if(nowans > minn || dep > 20) return;
    else
    {
        bool od = 0;
        for(int i = 1; i <= len; i ++ )
            if(rec[dep][i] & 1)
            {
                od = true;
                break;
            }
        
        if(!od)
        {
            for(int i = 1; i <= len; i ++ )
                rec[dep + 1][i] = rec[dep][i] >> 1;
            len = unique(rec[dep + 1] + 1, rec[dep + 1] + len + 1) - rec[dep + 1] - 1;
            dfs(dep + 1, len);
        }
        else
        {
            for(int i = 1; i <= len; i ++ )
                if(rec[dep][i] & 1)
                    rec[dep + 1][i] = (rec[dep][i] - 1) >> 1;
                else rec[dep + 1][i] = rec[dep][i] >> 1;

            sec[++ nowans] = (1 << dep);
            int l = unique(rec[dep + 1] + 1, rec[dep + 1] + len + 1) - rec[dep + 1] - 1;
            dfs(dep + 1, l);
            nowans --;

            for(int i = 1; i <= len; i ++ )
                if(rec[dep][i] & 1)
                    rec[dep + 1][i] = (rec[dep][i] + 1) >> 1;
                else rec[dep + 1][i] = rec[dep][i] >> 1;

            sec[++ nowans] = -(1 << dep);
            l = unique(rec[dep + 1] + 1, rec[dep + 1] + len + 1) - rec[dep + 1] - 1;
            dfs(dep + 1, l); 
            nowans --;
        }
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;
    
    for(int i = 1; i <= n; i ++ ) rec[0][i] = a[i];
    dfs(0, n);

    printf("%d\n", minn);
    for(int i = 1; i <= minn; i ++ )
        printf("%d ", ans[i]);

    return 0;
}

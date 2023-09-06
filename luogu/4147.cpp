#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PII;

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
int a[N][N], h[N];
int l[N], r[N];
int tt;
int n, m;
int ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    // int T = read();
    int T = 1;
    while(T -- )
    {    
        memset(h, 0, sizeof h);
        memset(a, 0, sizeof a);
        ans = 0;
        n = read(), m = read();
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= m; j ++ )
            {
                char s[2];
                scanf("%s", s);
                a[i][j] = (s[0] == 'F' ? 1 : 0);
            }

        for(int i = 1; i <= n; i ++ )
        {
            int maxn = 0;
            for(int j = 1; j <= m; j ++ )
            {
                if(a[i][j]) h[j] ++;
                else h[j] = 0;
                l[j] = r[j] = j;
            }

            for(int j = 1; j <= m; j ++ )
                while(l[j] > 1 && h[j] <= h[l[j] - 1]) l[j] = l[l[j] - 1];
                
            for(int j = m; j >= 1; j -- )
                while(r[j] < m && h[j] <= h[r[j] + 1]) r[j] = r[r[j] + 1];

            for(int j = 1; j <= m; j ++ )
                maxn = max(maxn, (r[j] - l[j] + 1) * h[j]);
            
            ans = max(ans, maxn);
        }

        printf("%d\n", 3 * ans);
        // if(T) puts("");
    }

    return 0;
}
#define LOCAL
/*#include <bits/stdc++.h>
using namespace std;
#define int long long
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

const int N = 17, M = 1 << 16;
int f[N][M];
int a[N];
int n, s;
int ans;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> s;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    for(int i = 1; i <= n; i ++ ) f[i][1 << (i - 1)] = 1;

    for(int j = 1; j < 1 << n; j ++ )
        for(int i = 1; i <= n; i ++ )
        {
            if(!(j >> (i - 1) & 1)) continue;

            for(int k = 1; k <= n; k ++ )
            {
                if(j >> (k - 1) & 1) continue;
                if(abs(a[i] - a[k]) > s) f[k][j | (1 << (k - 1))] += f[i][j];
            }
        }

    for(int i = 1; i <= n; i ++ ) ans += f[i][(1 << n) - 1];

    cout << ans << endl;
    
    return 0;
}
*/

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

const int N = 17, M = 1 << 16;
int a[N];
int n, k;
ll ans;

void dfs(int u, int s)
{
    if(s == (1 << n) - 1) 
    {
        ans ++;
        return;
    }
    
    for(int i = 1; i <= n; i ++ )
        if(!(s >> (i - 1) & 1) && abs(a[i] - a[u]) > k)
            dfs(i, s | (1 << (i - 1)));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> k;
    for(int i = 1; i <= n; i ++ ) cin >> a[i];

    a[0] = -0x3f3f3f3f;
    dfs(0, 0);

    cout << ans << endl;
    
    return 0;
}
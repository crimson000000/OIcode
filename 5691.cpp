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

const int N = 10;
int x[N], k[N], p[N];
unordered_map<int, int> cnt;
int n, m;
int ans;

int qmi(int x, int k)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = res * x;
        x = x * x;
        k >>= 1;
    }
    return res;
}

void dfs1(int dep, int sum)
{
    if(dep > (n >> 1))
    {
        cnt[sum] ++;
        return;
    }
    for(int i = 1; i <= m; i ++ )
    {
        x[dep] = i;
        dfs1(dep + 1, sum + k[dep] * qmi(i, p[dep]));
    }
}

void dfs2(int dep, int sum)
{
    if(dep == n + 1)
    {
        ans += cnt[sum];
        return;
    }
    for(int i = 1; i <= m; i ++ )
    {
        x[dep] = i;
        dfs2(dep + 1, sum - k[dep] * qmi(i, p[dep]));
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        k[i] = read(), p[i] = read();

    dfs1(1, 0);
    dfs2((n >> 1) + 1, 0);

    cout << ans << endl;
    
    return 0;
}

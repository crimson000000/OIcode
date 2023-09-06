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

const int N = 5e5 + 10;
char s[N];
int f[N][3][2]; //0为绿，1红，2蓝   0最小，1最大
int cnt, maxn, minn = 0x3f3f3f3f;

void dfs(int u)
{
    if(s[u] == '0')
    {
        f[u][0][0] = 1;
        f[u][1][0] = 0;
        f[u][2][0] = 0;
        f[u][0][1] = 1;
        f[u][1][1] = 0;
        f[u][2][1] = 0;
        return ;
    }

    dfs(++ cnt);
    if(s[u] == '1')
    {
        f[u][0][0] = min(f[u + 1][1][0], f[u + 1][2][0]) + 1;
        f[u][1][0] = min(f[u + 1][0][0], f[u + 1][2][0]);
        f[u][2][0] = min(f[u + 1][1][0], f[u + 1][0][0]);

        f[u][0][1] = max(f[u + 1][1][1], f[u + 1][2][1]) + 1;
        f[u][1][1] = max(f[u + 1][0][1], f[u + 1][2][1]);
        f[u][2][1] = max(f[u + 1][1][1], f[u + 1][0][1]);
    }
    else
    {
        int k = ++ cnt;
        dfs(k);
        f[u][0][0] = min(f[u + 1][1][0] + f[k][2][0], f[u + 1][2][0] + f[k][1][0]) + 1;
        f[u][1][0] = min(f[u + 1][0][0] + f[k][2][0], f[u + 1][2][0] + f[k][0][0]);
        f[u][2][0] = min(f[u + 1][0][0] + f[k][1][0], f[u + 1][1][0] + f[k][0][0]);

        f[u][0][1] = max(f[u + 1][1][1] + f[k][2][1], f[u + 1][2][1] + f[k][1][1]) + 1;
        f[u][1][1] = max(f[u + 1][0][1] + f[k][2][1], f[u + 1][2][1] + f[k][0][1]);
        f[u][2][1] = max(f[u + 1][0][1] + f[k][1][1], f[u + 1][1][1] + f[k][0][1]);
    }

    maxn = max(maxn, f[u][0][1]);
    maxn = max(maxn, f[u][1][1]);
    maxn = max(maxn, f[u][2][1]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    dfs(++ cnt);

    cout << maxn << ' ' << min(f[1][0][0], min(f[1][2][0], f[1][1][0])) << endl;
    
    return 0;
}

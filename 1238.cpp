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

const int N = 1010;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
int g[N][N];
PII ans[N];
bool st[N][N];
int cnt;
int stx, sty, edx, edy;
int n, m;
bool flag;

bool vaild(int a, int b)
{
    return (g[a][b] != 0 && !st[a][b]);
}

void print()
{
    flag = true;
    for(int i = 1; i <= cnt; i ++ )
        printf("(%d,%d)->", ans[i].first, ans[i].second);
    printf("(%d,%d)\n", edx, edy);
}

void dfs(int x, int y)
{
    if(x == edx && y == edy)
    {
        print();
        return;
    }
    for(int i = 0; i < 4; i ++ )
    {
        int a = x + dx[i], b = y + dy[i];
        if(!vaild(a, b)) continue;
        st[x][y] = true;
        ans[++ cnt] = {x, y};
        dfs(a, b);
        cnt --;
        st[x][y] = false;
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
        for(int j = 1; j <= m; j ++ )
            g[i][j] = read();

    stx = read(), sty = read(), edx = read(), edy = read();
    // ans[++ cnt] = {stx, sty};
    dfs(stx, sty);

    if(!flag) puts("-1");
    
    return 0;
}
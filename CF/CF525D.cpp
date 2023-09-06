#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

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

const int N = 2010;
char a[N][N];
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
int n, m;

inline bool check(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > m) return false;
    if(a[x][y] != '*') return false;
    if(a[x - 1][y - 1] == '.' && a[x - 1][y] == '.' && a[x][y - 1] == '.') return true;
    if(a[x - 1][y] == '.' && a[x - 1][y + 1] == '.' && a[x][y + 1] == '.') return true;
    if(a[x][y - 1] == '.' && a[x + 1][y - 1] == '.' && a[x + 1][y] == '.') return true;
    if(a[x][y + 1] == '.' && a[x + 1][y] == '.' && a[x + 1][y + 1] == '.') return true;
    return false;
}

void dfs(int x, int y)
{
    if(!check(x, y)) return;
    a[x][y] = '.';
    for(int i = 0; i < 8; i ++ )
        dfs(x + dx[i], y + dy[i]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
        scanf("%s", a[i] + 1);
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            dfs(i, j);
        
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= m; j ++ )
            putchar(a[i][j]);
        puts("");
    }

    return 0;
}
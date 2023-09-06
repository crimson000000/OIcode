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
const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, -1, 1, -1, 1};
int n;
int h[N][N];
bool st[N][N];
bool up, down;
int cntup, cntdown;

#define x first
#define y second

bool vaild(int a, int b)
{
    return !(a > n || a < 1 || b > n || b < 1);
}

void bfs(int x, int y)
{
    up = false, down = false;
    queue<PII> q;
    q.push({x, y});
    st[x][y] = true;

    while(q.size())
    {
        auto t = q.front();
        q.pop();

        // printf("%d %d\n", t.x, t.y);
        
        for(int i = 0; i < 8; i ++ )
        {
            int a = t.x + dx[i], b = t.y + dy[i];
            if(!vaild(a, b)) continue; 
            
            if(h[a][b] < h[x][y]) down = true;
            if(h[a][b] > h[x][y]) up = true;
            if(h[a][b] == h[x][y] && !st[a][b])
            {
                q.push({a, b});
                st[a][b] = true;
            }
        }
    }

    if(down && !up) cntdown ++;
    if(up && !down) cntup ++;
    if(!down && !up) cntdown ++, cntup ++;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            h[i][j] = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            if(!st[i][j])
            {
                bfs(i, j);
                // puts("");
                // for(int i = 1; i <= n; i ++ )
                // {
                //     for(int j = 1; j <= n; j ++ )
                //         cout << st[i][j] << ' ';
                //     puts("");
                // }
            }

    cout << cntdown << ' ' << cntup << endl;

    return 0;
}

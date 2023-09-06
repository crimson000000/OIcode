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

const int N = 1010;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int mp[N][N];
int n, m;

struct state
{
    int x, y;
};

inline bool vaild(int x, int y)
{
    return (x <= n && x > 0 && y <= m && y > 0 &&
             mp[x][y] != 1 && mp[x][y] != 3);
}

queue<state> q1, q2;
bitset<N> st1[N], st2[N];
int dist1[N][N], dist2[N][N];
void bfs()
{
    memset(dist1, 0x3f, sizeof dist1);
    memset(dist2, 0x3f, sizeof dist2);
    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j] == 2) 
            {
                q1.push({i, j});
                dist1[i][j] = 0;
            }
            if(mp[i][j] == 3) 
            {
                q2.push({i, j});
                dist2[i][j] = 0;
            }
        }
    
    while(q1.size() || q2.size())
    {
        state u;
        if(q1.size())
        {
            u = q1.front();
            q1.pop();
            
            for(int i = 0; i < 4; i ++ )
            {
                int a = u.x + dx[i], b = u.y + dy[i];
                if(!vaild(a, b)) continue;
                if(st1[a][b]) continue;
                st1[a][b] = true;
                dist1[a][b] = dist1[u.x][u.y] + 1;
                q1.push({a, b});
            }
        }
        if(q2.size())
        {
            u = q2.front();
            q2.pop();
            
            for(int i = 0; i < 4; i ++ )
            {
                int a = u.x + dx[i], b = u.y + dy[i];
                if(!vaild(a, b)) continue;
                if(st2[a][b]) continue;
                st2[a][b] = true;
                dist2[a][b] = dist2[u.x][u.y] + 1;
                q2.push({a, b});
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j] == 4)
                ans = min(ans, dist1[i][j] + dist2[i][j]);
        }
    
    cout << ans << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read(), n = read();
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            mp[i][j] = read();

    bfs();

    return 0;
}
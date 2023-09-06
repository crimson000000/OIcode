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

const int N = 710;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
char mp[N][N];
bool vik[N][N];
int n, m;

struct state
{
    int x, y;
}st, ed, vi;

queue<state> q1, q2, q;
bitset<N> st1[N], st2[N], vis[N], ma[N];
int d[N][N], d1[N][N];

inline void extend(int x, int y)
{
    for(int i = x; i >= 1 && mp[i][y] != 'I'; i -- ) 
        vik[i][y] = true;
    for(int i = x; i <= n && mp[i][y] != 'I'; i ++ ) 
        vik[i][y] = true;
    for(int i = y; i >= 1 && mp[x][i] != 'I'; i -- ) 
        vik[x][i] = true;
    for(int i = y; i <= m && mp[x][i] != 'I'; i ++ ) 
        vik[x][i] = true;
}

bool bfs()
{
    q1.push(st), q2.push(vi);
    st2[st.x][st.y] = true;
    st1[vi.x][vi.y] = true;
    d[vi.x][vi.y] = 0;
    d1[st.x][st.y] = 0;
    int step = -1;
    while(!q1.empty())
    {
        step ++;
        

        
        while(q2.size() && d[q2.front().x][q2.front().y] <= step)
        {
            auto a = q2.front();
            q2.pop();

            // printf("(%d, %d)\n", a.x, a.y);

            for(int i = 0; i < 4; i ++ )
            {
                int x = a.x + dx[i], y = a.y + dy[i];
                if(st1[x][y]) continue;
                if(x < 1 || x > n || y < 1 || y > m) continue;
                if(mp[x][y] == 'I') continue;
                d[x][y] = d[a.x][a.y] + 1;
                st1[x][y] = true;
                extend(x, y);
                q2.push({x, y});
            }
        }

            // for(int i = 1; i <= n; i ++ )
            // {
            //     for(int j = 1; j <= m; j ++ )
            //     {
            //         if(!vik[i][j]) cout << "0 ";
            //         else cout << 1 << ' ';
            //     }
            //     puts("");
            // }

            // puts("");
        while(q1.size() && d1[q1.front().x][q1.front().y] <= step)
        {
            auto a = q1.front();
            q1.pop();

            // cout << a.x << ' ' << a.y << ' ' << d1[a.x][a.y] << endl;

            if(a.x == ed.x && a.y == ed.y) return true;

            for(int i = 0; i < 4; i ++ )
            {
                int x = a.x + dx[i], y = a.y + dy[i];
                if(st2[x][y]) continue;
                if(x < 1 || x > n || y < 1 || y > m) continue;
                if(vik[x][y]) continue;
                if(mp[x][y] == 'I') continue;
                if(vik[x][y]) continue;
                st2[x][y] = true;
                d1[x][y] = d1[a.x][a.y] + 1;
                
                q1.push({x, y});
            }

            // printf("peo:\n");
            // for(int i = 1; i <= n; i ++ )
            // {
            //     for(int j = 1; j <= m; j ++ )
            //     {
            //         cout << d1[i][j] << ' ';
            //     }
            //     puts(""); 
            // }
            // puts("");
        }
    }
    // for(int i = 1; i <= n; i ++ )
    //     for(int j = 1; j <= m; j ++ )
    //         if(d1[i][j] < vik[i][j] && mp[i][j] != 'I')
    //             ma[i][j] = true;
        
    // for(int i = 1; i <= n; i ++ )
    // {
    //     for(int j = 1; j <= m; j ++ )
    //         if(ma[i][j])
    //             cout << 1 << ' ';
    //         else cout << 0 << ' ';
    //     puts("");
    // }       
    
    // q.push(st);
    // vis[st.x][st.y] = true;
    // while(q.size())
    // {
    //     auto a = q.front();
    //     q.pop();

    //     for(int i = 0; i < 4; i ++ )
    //     {
    //         int x = a.x + dx[i], y = a.y + dy[i];
    //         if(vis[x][y]) continue;
    //         if(x < 1 || x > n || y < 1 || y > m) continue;
    //         if(!ma[x][y]) continue;
    //         if(mp[x][y] == 'I') continue;
    //         vis[x][y] = true;
    //         if(x == ed.x && y == ed.y) return true;
    //         q.push({x, y});
    //     }
    // }

    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= n; i ++ ) scanf("%s", mp[i] + 1);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            if(mp[i][j] == 'Y') st.x = i, st.y = j;
            if(mp[i][j] == 'V') vi.x = i, vi.y = j;
            if(mp[i][j] == 'T') ed.x = i, ed.y = j;
        }

    if(bfs()) puts("YES");
    else puts("NO");

    return 0;
}
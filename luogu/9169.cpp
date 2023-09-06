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

const int N = 11, M = 5e5 + 10, INF = 0x3f3f3f3f;
int dx_b[] = {-1, 0, 0}, dy_b[] = {0, -1, 1};
int dx_r[] = {0, -1, 0, 1}, dy_r[] = {-1, 0, 1, 0};
int ff[N][N][N][N][N][N], cnt;
PII wp[M];
int dist[M];
vector<int> tr[M];
char mp[N][N];
int n, m;

struct node
{
    int k;
    int x, y, a, b, c, d;
};

queue<node> q;
queue<int> que;

inline bool check_b(int x, int y)
{
    return (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#');
}

inline bool check_r(int a, int b, int c, int d)
{
    return (a >= 1 && a <= n && b >= 1 && b <= m && (a != c || b != d) && mp[a][b] != '#');
}

inline bool check(int a, int b, int c, int d)
{
    return (a < c || (a == c && b < d));
}

inline void init()
{
    cnt = 0;
    for(int i = 1; i < N; i ++ )
        for(int j = 1; j < N; j ++ )
            for(int a = 1; a < N; a ++ )    
                for(int b = 1; b < N; b ++ )    
                    for(int c = 1; c < N; c ++ )
                        for(int d = 1; d < N; d ++ )    
                            if(check(a, b, c, d))
                                ff[i][j][a][b][c][d] = ++ cnt;
}

inline int find(node t)
{
    int x = t.x, y = t.y, a = t.a, b = t.b, c = t.c, d = t.d;
    if(check(a, b, c, d))
        return ff[x][y][a][b][c][d];
    return ff[x][y][c][d][a][b];
}

bitset<M> st;
inline void bfs(int ax, int ay, int dx, int dy, int fx, int fy)
{
    q.push({1, ax, ay, dx, dy, fx, fy});
    for(int i = 1; i < M; i ++ )    
        wp[i] = {INF, 0}, tr[i].clear();

    while(q.size())
    {
        auto u = q.front();
        q.pop();
        int t = find(u);

        int x = u.x, y = u.y, a = u.a, b = u.b, c = u.c, d = u.d;
        // printf("%d (%d, %d) (%d, %d) (%d, %d)\n", u.k, x, y, a, b, c, d);
        if(x == 1) 
            wp[t] = {1, 0}, que.push(t);
        else if((x == a && y == b) || (x == c && y == d))
            wp[t] = {1, 0}, que.push(t);
        else
        {
            if(u.k)
            {
                for(int i = 0; i < 4; i ++ )
                {
                    int e = a + dx_r[i], f = b + dy_r[i];
                    if(!check_r(e, f, c, d)) continue;
                    node ns = {0, x, y, e, f, c, d};
                    int ts = find(ns);
                    tr[ts].push_back(t);
                    dist[t] ++;
                    if(!st[ts])
                    {
                        // if(ts == ff[8][8][4][3][8][5]) puts("fucc");
                        st[ts] = true, q.push(ns);
                    }
                }
                for(int i = 0; i < 4; i ++ )
                {
                    int e = c + dx_r[i], f = d + dy_r[i];
                    if(!check_r(e, f, a, b)) continue;
                    node ns = {0, x, y, a, b, e, f};
                    int ts = find(ns);
                    tr[ts].push_back(t);
                    dist[t] ++;
                    if(!st[ts])
                    {
                        // if(ts == ff[8][8][4][3][8][5]) puts("fucc");
                        st[ts] = true, q.push(ns);
                    }
                }
            }
            else
            {
                for(int i = 0; i < 3; i ++ )
                {
                    int e = x + dx_b[i], f = y + dy_b[i];
                    
                    if(!check_b(e, f)) continue;
                    // cout << e << ' ' << f << endl;
                    node ns = {1, e, f, a, b, c, d};
                    // printf("%d %d %d %d %d %d\n", e, f, a, b, c, d);
                    int ts = find(ns);
                    tr[ts].push_back(t);
                    dist[t] ++;
                    if(!st[ts])
                    {
                        // if(ts == ff[8][8][4][3][8][5]) puts("fucc");
                        st[ts] = true, q.push(ns);
                    }
                }
            }
            if(!dist[t])
                wp[t] = {1, 0}, que.push(t);
        }
    }
}

bitset<M> vis;
inline void toposort()
{
    while(que.size())
    {
        int u = que.front();
        que.pop();
        if(wp[u].first == 1)
        {
            for(auto v : tr[u])
            {
                if(wp[v].first == INF)
                    wp[v] = {0, wp[u].second + 1};
                if(!vis[v])
                    vis[v] = true, que.push(v);
            }
        }
        else
        {
            for(auto v : tr[u])
            {
                dist[v] --;
                if(wp[v].first == INF)
                    wp[v].second = wp[u].second + 1;
                if(!dist[v])
                {
                    if(wp[v].first == INF)
                        wp[v].first = 1;
                    if(!vis[v])
                        vis[v] = true, que.push(v);
                }
            }
        }
    }
}

inline void solve()
{
    memset(dist, 0, sizeof dist);
    vis.reset();
    st.reset();

    n = read(), m = read();
    // cout << n << ' ' << m << endl;

    for(int i = 1; i <= n; i ++ ) scanf("%s", mp[i] + 1);

    // cout << check_b(8, 8) << endl;

    int ax = 0, ay = 0, dx = 0, dy = 0, fx = 0, fy = 0;
    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= m; j ++ )
            if(mp[i][j] == 'X') ax = i, ay = j;
            else if(mp[i][j] == 'O') 
            {
                if(!dx && !dy) dx = i, dy = j;
                else fx = i, fy = j;
            }
    
    bfs(ax, ay, dx, dy, fx, fy);

    // cout << que.size() << endl;

    toposort();

    int ans = ff[ax][ay][dx][dy][fx][fy];
    if(wp[ans].first == INF) puts("Tie");
    else if(wp[ans].first == 1)
        printf("Black %d\n", wp[ans].second);
    else printf("Red %d\n", wp[ans].second);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init();
    // cout << ff[8][8][4][3][8][5] << endl;
    int id = read(), T = read();
    while(T -- ) solve();

    return 0;
}
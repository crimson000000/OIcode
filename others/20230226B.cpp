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

const int N = 110, INF = 0x3f3f3f3f;
int g[N][N];
int dist[N];
bool st[N];
int n;

bool check(int s)
{
    memset(dist, 0, sizeof dist);
    queue<int> q;
    dist[1] = s;
    q.push(1);
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = 1; i <= n; i ++ )
            if(g[t][i])
            {
                if(dist[i] < dist[t] * 2 + g[t][i])
                {
                    dist[i] = dist[t] * 2 + g[t][i];
                    if(!st[i])
                    {
                        q.push(i);
                        st[i] = true;
                    }
                }
            }
    }
    if(dist[n] <= 0) return false;
    else return true;
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
        {
            int a = read();
            g[i][j] = a;
        }

    int l = 1, r = 1e6;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << l << endl;
    
    return 0;
}

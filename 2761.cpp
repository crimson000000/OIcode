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

const int N = 3e6 + 10;
int dist[N];
bool st[N];
int b1[N], b2[N], f1[N], f2[N];
int t[N];
int n, m;

bool check(int s, int ver)
{
    return ((s | b1[ver]) == s) && ((b2[ver] & s) == 0);
}

int fix(int t, int ver)
{
    return (t | f1[ver] | f2[ver]) ^ f1[ver];
}

inline void bfs()
{
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    dist[(1 << n) - 1] = 0;
    q.push((1 << n) - 1);
    st[(1 << n) - 1] = true;
    while(q.size())
    {
        int tt = q.front();
        q.pop();
        st[tt] = false;

        for(int i = 1; i <= m; i ++ )
            if(check(tt, i))
            {
                // cout << i << endl;
                int state = fix(tt, i);
                // cout << state << endl;
                if(dist[state] > dist[tt] + t[i])
                {
                    dist[state] = dist[tt] + t[i];
                    if(!st[state])
                    {
                        q.push(state);
                        st[state] = true;
                    }
                }
            }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = 0;
    while(n = read(), m = read(), n && m)
    {
        memset(b1, 0, sizeof b1);
        memset(b2, 0, sizeof b2);
        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);
        memset(t, 0, sizeof t);
        memset(st, 0, sizeof st);
        printf("Product %d\n", ++ T);
        for(int i = 1; i <= m; i ++ )
        {
            t[i] = read();
            string s1;
            cin >> s1;
            for(int j = 0; j < s1.size(); j ++ )
            {
                if(s1[j] == '-')
                    b2[i] |= (1 << j);
                else if(s1[j] == '+')
                    b1[i] |= (1 << j);
            }

            string s2;
            cin >> s2;
            for(int j = 0; j < s2.size(); j ++ )
                if(s2[j] == '+')
                    f2[i] |= (1 << j);
                else if(s2[j] == '-')
                    f1[i] |= (1 << j);
        }

        bfs();

        if(dist[0] == 0x3f3f3f3f) puts("Bugs cannot be fixed.\n");
        else printf("Fastest sequence takes %d seconds.\n\n", dist[0]);
    }
    
    return 0;
}

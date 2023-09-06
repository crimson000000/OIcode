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

const int N = 1e5 + 10;
int a[N * 40], start[N];
int dist[N];
bool st[N];
int n, m, cnt;

int gcd(int a, int b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

bool check()
{
    int gcdd = a[1];
    for(int i = 2; i <= cnt; i ++ )
        gcdd = gcd(gcdd, a[i]);
    if(gcdd == 1) return false;
    return true;
}

void SPFA()
{
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    q.push(0);
    st[0] = true;
    dist[0] = 0;

    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = 1; i < cnt; i ++ )
        {
            int j = (t + a[i]) % a[0];
            if(dist[j] > dist[t] + a[i])
            {
                dist[j] = dist[t] + a[i];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
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

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        start[i] = read();
        for(int j = 0; j <= m; j ++ )
        {
            a[cnt ++ ] = start[i] - j;
            if(start[i] - j == 1)
            {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    sort(a, a + cnt);
    cnt = unique(a, a + cnt) - a;

    // cout << cnt << endl;

    // for(int i = 0; i < cnt; i ++ ) cout << a[i] << ' ';

    if(check())
    {
        puts("-1");
        return 0;
    }

    SPFA();

    int ans = 0;
    for(int i = 1; i < a[0]; i ++ ) ans = max(ans, dist[i]);

    cout << ans - a[0] << endl;
    
    return 0;
}

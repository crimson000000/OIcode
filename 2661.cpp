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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int cnt[N], d[N];
bool st[N];
int n, ans = 0x3f3f3f3f;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void topsort()
{
    queue<int> q;
    for(int i = 1; i <= n; i ++ )
        if(!d[i])
            q.push(i), st[i] = true;

    while(q.size())
    {
        int t = q.front();
        q.pop();

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j] --;
            if(!d[j]) q.push(j), st[j] = true;
        }
    }
}

void dfs(int s, int now, int l)
{
    if(s == now)
    {
        ans = min(ans, l);
        return;
    }

    for(int i = h[now]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(st[j]) continue;
        st[j] = true;
        dfs(s, j, l + 1);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();
    
    for(int i = 1; i <= n; i ++ )
    {
        int t = read();
        add(i, t);
        d[t] ++;
    }

    topsort();

    for(int i = 1; i <= n; i ++ )
        if(!st[i])
            for(int j = h[i]; j != -1; j = ne[j])
            {
                int k = e[j];
                if(st[k]) continue;
                dfs(i, k, 1);
            }

    cout << ans << endl;
    
    return 0;
}

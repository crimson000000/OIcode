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
int h[N], e[5 * N], ne[5 * N], idx;
int low[N], dfn[N], tim;
int stk[N], top;
bool in_stk[N];
int id[N], din[N], dout[N], cnt;
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u, in_stk[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if(in_stk[j]) 
            low[u] = min(low[u], dfn[j]);
    }

    if(low[u] == dfn[u])
    {
        int y;
        cnt ++;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = cnt;
        } while(y != u);
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
        int t;
        while(cin >> t, t)
        {
            add(i, t);
        }
    }

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= n; i ++ )
        for(int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            if(a != b)
            {
                din[b] ++;
                dout[a] ++;
            }
        }

    int a = 0, b = 0;
    for(int i = 1; i <= cnt; i ++ )
    {
        if(!din[i]) a ++;
        if(!dout[i]) b ++;
    }

    cout << a << endl;
    if(cnt == 1) cout << 0 << endl;
    else cout << max(a, b) << endl;
    
    return 0;
}

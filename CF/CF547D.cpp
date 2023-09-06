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

const int N = 1e6 + 10, M = 2e6 + 10, NN = 2e5 + 10;
int h[N], e[M], ne[M], idx;
int n;
int x[NN], yyy[NN], du[N], res[NN];
bool vis[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ , du[a] ++;
}

void euler(int u)
{
    for(int &i = h[u]; i != -1; i = ne[i])
    {
        if(!vis[i])
        {
            vis[i] = vis[i ^ 1] = true;
            if(i & 1) res[i / 2 + 1] = 1;
            else res[i / 2 + 1] = 0;
            int j = e[i];
            euler(j);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    //图论记得初始化啊啊啊啊啊啊
    memset(h, -1, sizeof h);

    n = read();

    for(int i = 1; i <= n; i ++ )
    {
        int u = read(), v = read() + 200000;
        add(u, v), add(v, u);
    }

    for(int i = 1; i <= 400000; i ++ )
        if(du[i] & 1)
            add(0, i), add(i, 0);

    for(int i = 1; i <= 400000; i ++ ) euler(i);

    for(int i = 1; i <= n; i ++ )
        if(res[i]) cout << 'r';
        else cout << 'b';
    cout << endl;

    return 0;
}

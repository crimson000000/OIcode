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

const int N = 1510;
int h[N], e[N], ne[N], idx;
int match[N];
bool st[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool find(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!st[j])
        {
            st[j] = true;
            if(!match[j] || find(match[j]))
            {
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    m = read(), n = read();

    int x = read(), y = read();
    while(x != -1 || y != -1)
    {
        add(x, y);
        x = read(), y = read();
    }

    int cnt = 0;
    for(int i = 1; i <= m; i ++ )
    {
        memset(st, 0, sizeof st);
        if(find(i)) cnt ++;
    }

    cout << cnt << endl;
    for(int i = m + 1; i <= n; i ++ )
        if(match[i])
            printf("%d %d\n", match[i], i);
    
    return 0;
}

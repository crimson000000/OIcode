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

const int N = 110;
bitset<50> f[N];
bitset<50> a;
int n, m, cnt;

void dfs(int now)
{
    if(now == m + 1)
    {
        if(a.count() == n) cnt ++;
        return;
    }

    dfs(now + 1);

    auto t = a;
    a |= f[now];
    dfs(now + 1);
    a = t;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int cnt = read();
        while(cnt -- )
        {
            int a = read();
            f[i][a - 1] = true;
        }
    }

    dfs(0);

    cout << cnt / 2 << endl;
    
    return 0;
}

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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 5e5 + 10;
int d[N][30];
int pos[N][30];
int a[N];

void insert(int p, int pos[], int d[])
{
    int x = a[p];
    for(int i = 21; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                d[i] = x;
                pos[i] = p;
                return;
            }
            if(p > pos[i]) swap(p, pos[i]), swap(x, d[i]);
            x ^= d[i];
        }
    }
}

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    
    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 21; j >= 0; j -- )
            d[i][j] = d[i - 1][j], pos[i][j] = pos[i - 1][j];
        insert(i, pos[i], d[i]);
    }

    m = read();
    while(m -- )
    {
        int l = read(), r = read();
        int ans = 0;
        for(int i = 21; i >= 0; i -- )
            if(pos[r][i] >= l)
                ans = max(ans, ans ^ d[r][i]);
        printf("%d\n", ans);
    }
    
    return 0;
}

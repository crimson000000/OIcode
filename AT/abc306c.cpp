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

const int N = 1e6 + 10;
int cnt[N], pos[N];
int a[N];
int n;

inline bool cmp(int x, int y)
{
    return pos[x] < pos[y];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= 3 * n; i ++ )
    {
        int x = read();
        cnt[x] ++;
        if(cnt[x] == 2) pos[x] = i;
    }

    for(int i = 1; i <= n; i ++ ) a[i] = i;
    sort(a + 1, a + n + 1, cmp);

    for(int i = 1; i <= n; i ++ ) printf("%d ", a[i]);

    return 0;
}
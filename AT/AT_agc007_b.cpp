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

const int N = 20010;
int a[N], b[N], p[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = i * N;
        b[i] = (n - i + 1) * N;
    }

    for(int i = 1; i <= n; i ++ )
    {
        int p = read();
        a[p] += i;
    }

    for(int i = 1; i <= n; i ++ ) printf("%d ", a[i]);
    puts("");
    for(int i = 1; i <= n; i ++ ) printf("%d ", b[i]);

    return 0;
}
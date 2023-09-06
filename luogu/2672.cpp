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
int sum[N], h[N], p[N];
struct node
{
    int v, s;
    bool operator < (const node& a)
    {
        return v > a.v;
    }
}a[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i].s = read();
    for(int i = 1; i <= n; i ++ ) a[i].v = read();

    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++ ) p[i] = max(p[i - 1], 2 * a[i].s);
    for(int i = 1; i <= n; i ++ ) sum[i] = sum[i - 1] + a[i].v;
    for(int i = n; i >= 1; i -- ) h[i] = max(h[i + 1], 2 * a[i].s + a[i].v);

    for(int i = 1; i <= n; i ++ ) printf("%d\n", max(sum[i] + p[i], sum[i - 1] + h[i]));

    return 0;
}
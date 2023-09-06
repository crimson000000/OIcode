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

const int N = 2e6 + 10;
int a[N], tmp[N];
ll sum[30][2];
int n, m;

void merge(int l, int r, int dep)
{
    int mid = l + r >> 1;
    if(l == r) return;
    merge(l, mid, dep - 1);
    merge(mid + 1, r, dep - 1);
    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r)
    {
        if(a[i] < a[j])
        {
            sum[dep][1] += r - j + 1;
            i ++;
        }
        else j ++;
    }
    i = l, j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(a[i] > a[j])
        {
            sum[dep][0] += mid - i + 1;
            tmp[k ++ ] = a[j ++ ];
        }
        else tmp[k ++ ] = a[i ++ ];
    }
    while(i <= mid) tmp[k ++ ] = a[i ++ ];
    while(j <= r) tmp[k ++ ] = a[j ++ ];
    for(int i = l; i <= r; i ++ )
        a[i] = tmp[i - l];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= (1 << n); i ++ ) a[i] = read();
    merge(1, (1 << n), n);

    m = read();
    while(m -- )
    {
        int x = read();
        ll ans = 0;
        for(int i = 1; i <= n; i ++ )
        {
            if(i <= x) swap(sum[i][0], sum[i][1]);
            ans += sum[i][0];
        }
        printf("%lld\n", ans);
    }

    return 0;
}
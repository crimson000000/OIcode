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
int n, rt;
int a[N];
PII f[20][N];
int pos[N];
ll ans;

void init()
{
    for(int i = 1; i <= n; i ++ ) f[0][i] = {a[i], i};
    for(int i = 1; i <= 18; i ++ )
        for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
}

PII query(int l, int r)
{
    int k = log2(r - l + 1);
    return max(f[k][l], f[k][r - (1 << k) + 1]);
}

void solve(int l, int r)
{
    if(l >= r) return;
    int mid = query(l, r).second;
    if(mid - l < r - mid)
    {
        for(int i = l; i < mid; i ++ )
        {
            int t = pos[a[mid] - a[i]];
            if(t >= mid && t <= r) ans ++;
        }
    }
    else
    {
        for(int i = mid + 1; i <= r; i ++ )
        {
            int t = pos[a[mid] - a[i]];
            if(t <= mid && t >= l) ans ++;
        }
    }
    solve(l, mid - 1);
    solve(mid + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read(), pos[a[i]] = i;

    init();
    solve(1, n);
    
    cout << ans << endl;

    return 0;
}
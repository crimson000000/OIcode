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
int f[21][N], g[21][N];
int a[N], lg[N];
int n;

inline int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

void ST_pre()
{
    for(int i = 1; i <= n; i ++ ) f[0][i] = g[0][i] = a[i];
    for(int i = 1; i <= 20; i ++ )
        for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
        {
            f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            g[i][j] = gcd(g[i - 1][j], g[i - 1][j + (1 << (i - 1))]);
        }
}

inline int getmin(int l, int r)
{
    int k = lg[r - l + 1];
    return min(f[k][l], f[k][r - (1 << k) + 1]);
}

inline int getgcd(int l, int r)
{
    int k = lg[r - l + 1];
    return gcd(g[k][l], g[k][r - (1 << k) + 1]);
}

inline bool check(int len)
{
    for(int l = 1; l + len - 1 <= n; l ++ )
    {
        int r = l + len - 1;
        if(getmin(l, r) == getgcd(l, r)) return true;
    }
    return false;
}

vector<int> ans;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 2; i <= n; i ++ ) lg[i] = lg[i >> 1] + 1;

    for(int i = 1; i <= n; i ++ ) a[i] = read();

    ST_pre();

    int l = 0, r = n + 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }

    int len = l - 1, cnt = 0;
    for(int i = 1; i + len - 1 <= n; i ++ )
    {
        int j = i + len - 1;
        if(getmin(i, j) == getgcd(i, j)) 
        {
            cnt ++;
            ans.push_back(i);
        }
    }

    printf("%d %d\n", cnt, len - 1);
    for(auto a : ans) printf("%d ", a);

    return 0;
}
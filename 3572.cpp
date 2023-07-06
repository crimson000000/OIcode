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
int f[N];
int q[N], hh, tt;
int n, m, h[N];

void solve(int k)
{
    hh = 0, tt = -1;
    q[++ tt] = 1;

    for(int i = 2; i <= n; i ++ )
    {
        while(hh <= tt && i - q[hh] > k) hh ++;
        f[i] = f[q[hh]] + (h[q[hh]] <= h[i]);
        while(hh <= tt && (f[q[tt]] > f[i] || (f[q[tt]] == f[i] && h[q[tt]] <= h[i])))
            tt --;
        q[++ tt] = i;
    }

    cout << f[n] << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) h[i] = read();

    m = read();

    while(m -- )
    {
        int k = read();
        solve(k);
    }

    return 0;
}
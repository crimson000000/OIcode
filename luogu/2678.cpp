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
int l, n, m;
int d[N];

bool check(int mid)
{
    int cnt = 0, nowdist = 0;
    for(int i = 0; i < n; i ++ )
    {
        nowdist += d[i + 1] - d[i];
        if(nowdist >= mid) 
        {
            nowdist = 0;
            continue;
        }
        else 
        {
            cnt ++;
        }
    }
    return cnt <= m;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    l = read(), n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) d[i] = read();
    n ++;
    d[n] = l;

    int L = 0, R = 1e9 + 10;
    while(L < R)
    {
        int mid = L + R >> 1;
        if(check(mid)) L = mid + 1;
        else R = mid;
    }

    cout << L - 1 << endl;

    return 0;
}
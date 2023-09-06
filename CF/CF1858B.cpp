#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e5 + 10;
int s[N], delta[N];
int n, m, d;

inline void solve()
{
    n = read(), m = read(), d = read();
    for(int i = 1; i <= m; i ++ ) s[i] = read();

    s[0] = 1;
    int eat = 0;
    for(int i = 1; i <= m; i ++ )
    {
        int dis = s[i] - s[i - 1];
        if(s[i] != 1) eat += (dis - 1) / d + 1;
        // cout << eat << endl;
    }

    int dis = n - s[m];
    eat += dis / d + 1;
    // cout << eat << endl;
    
    s[m + 1] = n;
    int cnt = 0, minn = 0x3f3f3f3f;
    for(int i = 1; i < m; i ++ )
    {
        int d1 = s[i] - s[i - 1], d2 = s[i + 1] - s[i];
        int d3 = s[i + 1] - s[i - 1];
        int e1 = (d1 - 1) / d + 1 + (d2 ? (d2 - 1) / d + 1 : 1);
        int e2 = (d3 - 1) / d + 1;
        if(d3 % d == 0 && i == m) e2 ++;
        if(s[i] == 1)
        {
            minn = eat, cnt = 1;
            continue;
        }
        if(eat - e1 + e2 < minn) minn = eat - e1 + e2, cnt = 1;
        else if(eat - e1 + e2 == minn) cnt ++; 
        // cout << d1 << ' ' << d2 << ' ' << d3 << endl;
        // cout << e1 << ' ' << e2 << endl;
        // cout << eat - e1 + e2 << endl;
    } 

    int d1 = s[m] - s[m - 1], d2 = s[m + 1] - s[m];
    int d3 = s[m + 1] - s[m - 1];
    int e1, e2;
    if(s[m] == n)
    {
        if(d3 % d == 0) e1 = 0, e2 = 0;
        else e1 = 1, e2 = 0;
        if(eat - e1 + e2 < minn) minn = eat - e1 + e2, cnt = 1;
        else if(eat - e1 + e2 == minn) cnt ++; 
    }
    else
    {
        e1 = (d1 - 1) / d + 1 + (d2 - 1) / d + 1;
        if(d2 % d == 0) e1 ++;
        e2 = (d3 - 1) / d + 1;
        if(d3 % d == 0) e2 ++;
        if(eat - e1 + e2 < minn) minn = eat - e1 + e2, cnt = 1;
        else if(eat - e1 + e2 == minn) cnt ++; 
    }

    printf("%d %d\n", minn, cnt);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}
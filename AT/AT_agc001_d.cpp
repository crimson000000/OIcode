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

const int N = 1e6 + 10;
int n, m;
int A[N];
int a[N], tt = 0;
int b[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) 
    {
        a[i] = read();
        if(a[i] & 1)
        {
            b[++ tt] = i;
        }
    }

    if(tt > 2) 
    {
        puts("Impossible");
        return 0;
    }

    if(m == 1)
    {
        if (a[1] == 1) printf("%d\n1\n1", a[1], a[1] - 1);
	    else printf("%d\n2\n1 %d", a[1], a[1] - 1);
        return 0;
    }

    if(tt >= 1) swap(a[1], a[b[1]]);
    if(tt >= 2) swap(a[m], a[b[2]]);

    // for(int i = 1; i <= tt; i ++ ) cout << b[i] << endl;
    // cout << tt << endl;

    for(int i = 1; i <= m; i ++ ) printf("%d ", a[i]);
    puts("");

    tt = 0;
    int s1 = a[1], s2 = a[1] + 1;
    b[++ tt] = a[1] + 1;
    for(int i = 2; i < m; i ++ )
    {
        s1 += a[i];
        b[++ tt] = s1 + 1 - s2;
        s2 += b[tt];
        if(!b[tt]) tt --;
    }

    b[++ tt] = a[m] - 1;
    if(!b[tt]) tt --;
    printf("%d\n", tt);
    for(int i = 1; i <= tt; i ++ ) printf("%d ", b[i]);

    return 0;
}
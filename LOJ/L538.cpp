#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

using PII = pair<ll, ll>;

const int N = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int s[N];
int n, m;
int k;
ll a[N];

inline ll sgn(ll x)
{
    if(x < 0) return -1;
    else if(x > 0) return 1;
    return 0;
}

inline void solve()
{
    a[0] = read(), a[1] = read(), k = read();

    if(!a[0] && !a[1])
    {
        printf("%d %d\n", s[1], s[1]);
        return;
    }
    
    ll lmax = max(abs(a[0]), abs(a[1]));

    int M = 1;
    bool flag;
    do {
        M ++;
        a[M] = k * a[M - 1] + a[M - 2]; 
        flag = true;
        if(abs(a[M]) > lmax)
        {
            lmax = abs(a[M]);
            flag = false;
        }
    } while(sgn(a[M]) != sgn(a[M - 1]) || !a[M - 1] || flag);

    int mx = -1, mn = -1;
    ll maxn = -INF, minn = INF;
    int it;
    for(it = 1; it <= n && s[it] < M; it ++ )
    {
        if(a[s[it]] > maxn)
            maxn = a[s[it]], mx = s[it];
        if(a[s[it]] < minn)
            minn = a[s[it]], mn = s[it];
    }

    if(it <= n)
    {
        if(a[M] > 0)
        {
            mx = s[n];
            if(minn == INF)
                mn = s[it];
        }
        else
        {
            mn = s[n];
            if(maxn == -INF)
                mx = s[it];
        }
    }

    printf("%d %d\n", mx, mn);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
        s[i] = read();
    
    m = read();
    while(m -- ) solve();

    return 0;
} 
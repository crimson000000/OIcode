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
char s[N];
int rk[N], sa[N], cnt[N], oldrk[N], id[N];
int w, n, m, p, t;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);
    t = n;
    for(int i = n + 1; i <= 2 * n; i ++ ) s[i] = s[i - n];
    n <<= 1;

    m = 128;
    for(int i = 1; i <= n; i ++ ) rk[i] = s[i];
    for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
    for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = n; i > 0; i -- ) sa[cnt[rk[i]] -- ] = i;
    memcpy(oldrk + 1, rk + 1, n * sizeof(int));
    for(int i = 1; i <= n; i ++ ) 
    {
        if(oldrk[sa[i]] != oldrk[sa[i - 1]])
            rk[sa[i]] = ++ p;
        else rk[sa[i]] = p;
    }

    for(w = 1; w < n; w <<= 1)
    {
        m = p;
        p = 0;
        for(int i = n; i > n - w; i -- ) id[++ p] = i;
        for(int i = 1; i <= n; i ++ )
            if(sa[i] > w)
                id[++ p] = sa[i] - w;
        
        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= n; i ++ ) cnt[rk[id[i]]] ++;
        for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];
        memcpy(oldrk + 1, rk + 1, n * sizeof(int));
        for(int i = 1; i <= n; i ++ )
        {
            if(oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = p;
            else rk[sa[i]] = ++ p;
        } 
    }

    for(int i = 1; i <= n; i ++ )
        if(sa[i] <= t)
            putchar(s[sa[i] + t - 1]);

    return 0;
}
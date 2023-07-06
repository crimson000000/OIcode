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
char s[N << 1];
int rk[N << 1], sa[N << 1], id[N << 1], px[N << 1];
int oldrk[N << 1], cnt[N];
int n, w, m, p, i;

inline bool cmp(int x, int y)
{
    if(rk[x] == rk[y]) return rk[x + w] < rk[y + w];
    return rk[x] < rk[y];
}

inline bool cmp1(int x, int y, int w)
{
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    m = 127;
    for(int i = 1; i <= n; i ++ ) rk[i] = s[i];

    for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
    for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i -- ) sa[cnt[rk[i]] -- ] = i;
    swap(oldrk, rk);
    for(p = 0, i = 1; i <= n; i ++ )
    {
        rk[sa[i]] = cmp1(sa[i], sa[i - 1], 0) ? p : ++ p;
    }

    for(w = 1; w < n; w <<= 1)
    {
        m = p;
        for(p = 0, i = n; i > n - w; i -- ) id[++ p] = i;
        for(i = 1; i <= n; i ++ )
            if(sa[i] > w)
                id[++ p] = sa[i] - w;

        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= n; i ++ ) px[i] = rk[id[i]], ++ cnt[px[i]];
        for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i -- ) sa[cnt[px[i]] -- ] = id[i];

        swap(oldrk, rk);
        for(p = 0, i = 1; i <= n; i ++ )
        {
            rk[sa[i]] = cmp1(sa[i], sa[i - 1], w) ? p : ++ p;
        }
    }

    for(int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);

    return 0;
}
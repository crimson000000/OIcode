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
int fa[N / 2][20];
char s[N];
int a[N];
int n;

void init()
{
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= 19; j ++ )
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

namespace SA
{
    int sa[N], rk[N], rkk[N], rk2[N], cnt[N], tp[N];

    inline void countsort(int *sa, int *rk, int *tp, int m)
    {
        for(int i = 0; i <= m; i ++ ) cnt[i] = 0;
        for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
        for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i -- ) sa[cnt[rk[tp[i]]] -- ] = tp[i];
    }

    inline bool cmp(int i, int t)
    {
        return tp[sa[i]] == tp[sa[i - 1]] && tp[fa[sa[i]][t]] == tp[fa[sa[i - 1]][t]];
    }

    void solve()
    {
        int p = 0;
        for(int i = 1; i <= n; i ++ ) a[i] = s[i] - 'a' + 1, tp[i] = i;
        countsort(sa, a, tp, n);
        rk[sa[1]] = rkk[sa[1]] = p = 1;
        for(int i = 2; i <= n; i ++ )
        {
            rk[sa[i]] = a[sa[i - 1]] == a[sa[i]] ? p : ++ p;
            rkk[sa[i]] = i;
        }

        for(int w = 1, t = 0; w < n; w <<= 1, t ++ )
        {
            for(int i = 1; i <= n; i ++ ) rk2[i] = rkk[fa[i][t]];
            countsort(tp, rk2, sa, n);
            countsort(sa, rk, tp, p);
            swap(rk, tp);
            rk[sa[1]] = rkk[sa[1]] = p = 1;
            for(int i = 2; i <= n; i ++ )
            {
                rk[sa[i]] = cmp(i, t) ? p : ++ p;
                rkk[sa[i]] = i;
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 2; i <= n; i ++ )
    {
        fa[i][0] = read();
    }

    scanf("%s", s + 1);

    init();
    SA::solve();

    for(int i = 1; i <= n; i ++ ) printf("%d ", SA::sa[i]);

    return 0;
}
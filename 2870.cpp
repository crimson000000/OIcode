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
int sa[N], rk[N], id[N], oldrk[N], cnt[N];
char s[N << 1], t[N];
int n, m, range;

inline bool cmp(int x, int y, int w)
{
    return (oldrk[x] == oldrk[y]) && (oldrk[x + w] == oldrk[y + w]);    
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        char ch = getchar();
        if(ch >= 'A' && ch <= 'Z')
            t[i] = ch;
        else i --;
    }

    for(int i = 1; i <= n; i ++ )
    {
        s[i] = t[i];
        s[2 * n + 2 - i] = t[i];
    }

    m = 2 * n + 1;

    range = 128;
    for(int i = 1; i <= m; i ++ ) rk[i] = s[i], cnt[rk[i]] ++;
    for(int i = 1; i <= range; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = m; i; i -- ) sa[cnt[rk[i]] -- ] = i;
    swap(oldrk, rk);
    for(int i = 1, p = 0; i <= m; i ++ )
    {
        if(cmp(sa[i], sa[i - 1], 0))
            rk[sa[i]] = p;
        else rk[sa[i]] = ++ p;
    }

    range = m;
    for(int w = 1; w < m; w <<= 1)
    {
        int p = 0;
        for(int i = m; i > m - w; i -- ) id[++ p] = i;
        for(int i = 1; i <= m; i ++ )
            if(sa[i] > w)
                id[++ p] = sa[i] - w;

        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= m; i ++ ) cnt[rk[id[i]]] ++;
        for(int i = 1; i <= range; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = m; i; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];

        swap(oldrk, rk);
        for(int i = 1, p = 0; i <= m; i ++ )
        {
            if(cmp(sa[i], sa[i - 1], w))
                rk[sa[i]] = p;
            else rk[sa[i]] = ++ p;
        }
    }

    int cnt = 0;
    for(int front = 1, back = n; front <= back;)
    {
        if(rk[front] < rk[2 * n + 2 - back])
        {
            putchar(t[front]);
            front ++;
        }
        else
        {
            putchar(t[back]);
            back --;
        }
        cnt ++;
        if(cnt == 80) 
        {
            puts("");
            cnt = 0;
        }
    }

    return 0;
}
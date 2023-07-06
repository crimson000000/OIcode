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

const int N = 5e5 + 10, M = 1010;
int a[N], blo[N], L[N], R[N];
vector<int> pos[N];
int f[M][M];
int loc[N];
int cnt[N];
int n, m;
int B, T;
int lastans;

inline int query(int l, int r)
{
    if(blo[l] == blo[r] || blo[l] == blo[r] - 1)
    {
        int res = 0;
        for(int i = l; i <= r; i ++ )
        {
            cnt[a[i]] ++;
            res = max(res, cnt[a[i]]);
        }
        for(int i = l; i <= r; i ++ ) cnt[a[i]] = 0;
        return res;
    }

    int Lblock = blo[l], Rblock = blo[r];
    int res = f[Lblock + 1][Rblock - 1];
    
    for(int i = l; i <= R[Lblock]; i ++ )
    {
        while(loc[i] + res < pos[a[i]].size() && pos[a[i]][loc[i] + res] <= r)
            res ++;
    }
    for(int i = L[Rblock]; i <= r; i ++ )
    {
        while(loc[i] - res >= 0 && pos[a[i]][loc[i] - res] >= l)
            res ++;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    B = sqrt(n), T = n / B;

    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        pos[a[i]].push_back(i);
        loc[i] = pos[a[i]].size() - 1;
    }

    for(int i = 1; i <= T; i ++ ) 
        L[i] = (i - 1) * B + 1, R[i] = i * B;
    
    if(R[T] < n)
    {
        T ++;
        L[T] = R[T - 1] + 1;
        R[T] = n;
    }

    for(int i = 1; i <= T; i ++ )
        for(int j = L[i]; j <= R[i]; j ++ )
            blo[j] = i;
    
    for(int i = 1; i <= T; i ++ )
    {
        int res = 0;
        for(int j = i; j <= T; j ++ )
        {
            for(int k = L[j]; k <= R[j]; k ++ )
            {
                cnt[a[k]] ++;
                res = max(res, cnt[a[k]]);
            }
            f[i][j] = res;
        }
        memset(cnt, 0, sizeof cnt);
    }

    while(m -- )
    {
        int l = read(), r = read();
        l ^= lastans, r ^= lastans;
        printf("%d\n", lastans = query(l, r));
    }

    return 0;
}
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

const int N = 110, M = 410, OPLBX = 1e6 + 10;
int cnt[N];
int L[OPLBX], R[OPLBX], idx;
int a[M][M], p[N];
int n, m;

inline void move(int x, int y)
{
    idx ++;
    L[idx] = x, R[idx] = y;
    cnt[y] ++;
    a[y][cnt[y]] = a[x][cnt[x]];
    cnt[x] --;
}

inline int top(int x)
{
    return a[x][cnt[x]];
}

inline int count(int x, int y)
{
    int res = 0;
    for(int i = 1; i <= cnt[x]; i ++ ) 
        if(a[x][i] == y)
            res ++;
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        cnt[i] = m, p[i] = i;
        for(int j = 1; j <= m; j ++ ) a[i][j] = read();
    }

    cnt[n + 1] = 0, p[n + 1] = n + 1;

    for(int now = n; now >= 3; now -- )
    {
        int tmp = count(p[1], now);
        for(int i = 1; i <= tmp; i ++ ) move(p[now], p[now + 1]);
        for(int i = 1; i <= m; i ++ )
            if(top(p[1]) == now) move(p[1], p[now]);
            else move(p[1], p[now + 1]);
        
        for(int i = 1; i <= m - tmp; i ++ )
            move(p[now + 1], p[1]);
        
        for(int i = 1; i <= m; i ++ ) 
            if(top(p[2]) == now || cnt[p[1]] == m) move(p[2], p[now + 1]);
            else move(p[2], p[1]);

        swap(p[1], p[now]);
        swap(p[2], p[now + 1]);

        for(int k = 1; k < now; k ++ )
        {
            int tmp = count(p[k], now);
            for(int i = 1; i <= tmp; i ++ ) move(p[now], p[now + 1]);
            for(int i = 1; i <= m; i ++ )
                if(top(p[k]) == now) move(p[k], p[now]);
                else move(p[k], p[now + 1]);
            
            swap(p[k], p[now + 1]);
            swap(p[k], p[now]);
        }

        for(int i = 1; i < now; i ++ ) 
            while(top(p[i]) == now)
                move(p[i], p[now + 1]);
        
        for(int i = 1; i < now; i ++ ) 
            while(cnt[p[i]] < m)
                move(p[now], p[i]);
    }
    
    int tmp = count(p[1], 1);
    for(int i = 1; i <= tmp; i ++ ) move(p[2], p[3]);
    for(int i = 1; i <= m; i ++ )
        if(top(p[1]) == 1) move(p[1], p[2]);
        else move(p[1], p[3]);
    
    for(int i = 1; i <= tmp; i ++ ) move(p[2], p[1]);
    for(int i = 1; i <= m - tmp; i ++ ) move(p[3], p[1]);
    for(int i = 1; i <= tmp; i ++ ) move(p[3], p[2]);
    while(top(p[1]) == 2) move(p[1], p[3]);
    while(cnt[p[2]])
    {
        if(top(p[2]) == 1) move(p[2], p[1]);
        else move(p[2], p[3]);
    }

    printf("%d\n", idx);
    for(int i = 1; i <= idx; i ++ ) 
        printf("%d %d\n", L[i], R[i]);

    return 0;
}
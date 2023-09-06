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

const int N = 1e5 + 10, M = 1010;
int a[N], b[N];
int L[N], R[N];
int pos[N];
int f[N], cnt[N];
int B, T;
int n, m;

inline void build(int x)
{
    for(int i = L[x]; i <= R[x]; i ++ ) a[i] = max(1, a[i] - f[x]);
    f[x] = 0;
    for(int i = L[x]; i <= R[x]; i ++ )
    {
        if(a[i] < L[x]) b[i] = a[i];
        else b[i] = b[a[i]];
    }
}

inline void change(int l, int r, int val)
{
    int Lblock = pos[l], Rblock = pos[r];
    if(Lblock == Rblock)
    {
        for(int i = l; i <= r; i ++ ) a[i] = max(1, a[i] - val);
        build(Lblock);
        return;
    }
    else
    {
        for(int i = l; i <= R[Lblock]; i ++ ) a[i] = max(1, a[i] - val);
        for(int i = L[Rblock]; i <= r; i ++ ) a[i] = max(1, a[i] - val);
        build(Lblock), build(Rblock);
        for(int i = Lblock + 1; i < Rblock; i ++ )
        {
            ++ cnt[i];
            f[i] = min(f[i] + val, N);
            if(cnt[i] <= B) build(i);
        }
    }
}

inline int getb(int x)
{
    return max(1, b[x] - f[pos[x]]);
}

inline int lca(int x, int y)
{
    while(1)
    {
        if(pos[x] < pos[y]) swap(x, y);
        if(pos[x] != pos[y]) x = getb(x);
        else
        {
            if(getb(x) != getb(y)) x = getb(x), y = getb(y);
            else break;
        }
    }
    while(x != y)
    {
        if(x < y) swap(x, y);
        x = max(1, a[x] - f[pos[x]]);
    }
    return x;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    B = sqrt(n), T = n / B;

    for(int i = 1; i <= T; i ++ )
    {
        L[i] = (i - 1) * B + 1;
        R[i] = i * B;
    }

    if(R[T] < n)
    {
        T ++;
        L[T] = R[T - 1] + 1, R[T] = n;
    }

    for(int i = 1; i <= T; i ++ )
        for(int j = L[i]; j <= R[i]; j ++ )
            pos[j] = i;
    
    for(int i = 2; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= T; i ++ ) build(i);

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int l = read(), r = read(), x = read();
            change(l, r, x);
        } 
        else
        {
            int u = read(), v = read();
            printf("%d\n", lca(u, v));
        }
    }

    return 0;
}
#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, M = 1e5;
int a[N], pos[N];
bitset<N> x1, x2;
int cnt[N];
int ans[N];
int n, m;

struct quuery
{
    int op, l, r, x, id;
    bool operator < (const quuery& a) const
    {
        if(pos[l] != pos[a.l]) return pos[l] < pos[a.l];
        return pos[r] < pos[a.r];
    }
}q[N];

inline void add(int x)
{
    if(!cnt[a[x]]) x1[a[x]] = 1, x2[M - a[x]] = 1;
    cnt[a[x]] ++;
}

inline void sub(int x)
{
    cnt[a[x]] --;
    if(!cnt[a[x]]) x1[a[x]] = 0, x2[M - a[x]] = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    n = read(), m = read();
    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        pos[i] = i / _;
    }
    
    for(int i = 1; i <= m; i ++ )
    {
        int op = read(), l = read(), r = read(), x = read();
        q[i] = {op, l, r, x, i};
    }

    sort(q + 1, q + m + 1);

    int L = 1, R = 0;
    for(int i = 1; i <= m; i ++ )
    {
        while(R < q[i].r) add(++ R);
        while(L > q[i].l) add(-- L);
        while(R > q[i].r) sub(R -- );
        while(L < q[i].l) sub(L ++ );
        int op = q[i].op, x = q[i].x;
        if(op == 1) 
        {
            if((x1 & (x1 << x)).any()) ans[q[i].id] = 1;
        }
        else if(op == 2) 
        {
            if((x1 & (x2 >> (M - x))).any()) ans[q[i].id] = 1;
        }
        else
        {
            for(int a = 1; a <= x / a; a ++ )
            {
                if(x % a == 0)
                {
                    if(x1[a] && x1[x / a]) 
                        ans[q[i].id] = 1;
                }
            }
        }
    }

    for(int i = 1; i <= m; i ++ )
        if(ans[i]) puts("hana");
        else puts("bi");

    return 0;
}

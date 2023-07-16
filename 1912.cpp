#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;
typedef __int128 i128;

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
const ll UP = 1e18;
ld f[N];
ll s[N];
char ch[N >> 3][55];
int a[N];
int n, l, p;
int pre[N];
bool flag;

inline ld qmi(ld a, int k)
{
    ld res = 1;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

struct node
{
    int j, l, r;
}q[N];
int hh, tt;

inline ld w(int j, int i)
{
    return f[j] + qmi(abs(s[i] - s[j] + i - j - 1 - l), p);
}

inline int find(int t, int i)
{
    int l = q[t].l, r = q[t].r + 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(w(q[t].j, mid) > w(i, mid))   
            r = mid;
        else l = mid + 1;
    }
    // for(; l <= r; l ++ )
    //     if(w(q[t].j, l) >= w(i, l) || l == n + 1)
    //         return l;
    return l;
}

inline void insert(int i)
{
    while(hh <= tt && w(q[tt].j, q[tt].l) > w(i, q[tt].l)) tt --;
    if(hh > tt)
    {
        tt ++;
        q[tt].j = i;
        q[tt].l = i;
        q[tt].r = n;
        return;
    }
    // if(hh <= tt && w(q[tt].j, q[tt].r) <= w(i, q[tt].r))
    // {
    //     tt ++;
    //     q[tt].j = i;
    //     q[tt].l = q[tt - 1].r + 1;
    //     q[tt].r = n;
    //     return;
    // }
    int pos = find(tt, i);
    // cout << pos << endl;
    if(pos > n) return;
    q[tt].r = pos - 1;
    tt ++;
    q[tt].j = i;
    q[tt].l = pos;
    q[tt].r = n;
}

void solve()
{
    hh = 0, tt = -1;
    q[++ tt] = {0, 1, n};
    f[0] = 0;
    for(int i = 1; i <= n; i ++ )
    {
        while(hh <= tt && q[hh].r < i) hh ++;
        q[hh].l = i;
        f[i] = w(q[hh].j, i);
        // if(i == n) printf("%d\n", q[hh].j);
        pre[i] = q[hh].j;
        // cout << i << ' ' << (ll)w(q[hh].j, i) << endl;
        // if(f[i] <= UP) 
        // {
        //     printf("%d %lld\n", i, (ll)f[i]);
        //     printf("%d %d %d\n", q[hh].j, q[hh].l, q[hh].r);
        // }

        insert(i);

        // if(f[i] <= UP) 
        // {
        //     printf("%d %d %d\n", q[tt].j, q[tt].l, q[tt].r);
        // }
    }
    if(f[n] > UP) 
    {
        flag = true;
        return;
    }
}

void print(int l, int r)
{
    if(!r) return;
    print(pre[l - 1] + 1, l - 1);
    for(int i = l; i <= r; i ++ )
    {
        printf("%s", ch[i] + 1);
        if(i != r) putchar(' ');   
    }
    puts("");
}

// inline void bf()
// {
//     f[0] = 0;
//     for(int i = 1; i <= n; i ++ )
//     {
//         int pre = 0;
//         for(int j = 0; j < i; j ++ )
//         {
//             if(f[i] > w(j, i))
//             {
//                 pre = j;
//                 f[i] = min(UP + 10, (ll)w(j, i));
//             }
//         }
        
//         // printf("%d is transed by %d\n", i, pre);
//     }
//     if(f[n] > UP) 
//     {
//         puts("fuc");
//         return;
//     }
//     else cout << (ll)f[n] << endl;
// }

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        flag = false;
        n = read(), l = read(), p = read();
        memset(f, 0x3f, sizeof f);
        memset(s, 0, sizeof s);
        for(int i = 1; i <= n; i ++ )
        {
            scanf("%s", ch[i] + 1);
            a[i] = strlen(ch[i] + 1);
        }

        for(int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + a[i];

        // for(int i = 0; i <= n; i ++ )
        // {
        //     for(int j = i + 1; j <= n; j ++ )
        //         printf("%lld ", ll(w(i, j)));
        //     puts("");
        // }

        solve();

        if(!flag) cout << (ll)f[n] << endl;
        else puts("Too hard to arrange");

        if(!flag) print(pre[n] + 1, n);

        if(T > 0) puts("--------------------");
        else printf("--------------------");

        // bf();
    }

    return 0;
}

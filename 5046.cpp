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

// class istream{
//     char buf[13000003],*s;
//     public:
//         inline istream(){
//             buf[fread(s=buf,1,13000001,stdin)]='\n';
//         }
//         template<typename T>
//         inline void operator>>(T&rhs){
//             for(rhs=0;!isdigit(*s);++s);
//             while(isdigit(*s))rhs=rhs*10+(*s++&15);
//         }
// }in;

// struct ostream{
//     char buf[8000005],*s;
//     inline ostream(){s=buf;}
//     inline void operator<<(long long d){
//         if(!d){
//             *s++='0';
//         }else{
//             static long long w;
//             for(w=1;w<=d;w*=10);
//             for(;w/=10;d%=w)*s++=d/w^'0';
//         }
//         *s++='\n';
//     }
//     inline ostream&operator<<(const char&c){*s++=c;return*this;}
//     inline~ostream(){fwrite(buf,1,s-buf,stdout);}
// }out;

const int N = 1e6 + 10, M = 1e3 + 10;
int a[N], pos[N];
int n, m;
ll s[M][M];
int t[N];
int T, BL;
PII b[N];
ll lastans;
ll f[800][100010];

struct bit
{
    int c[N];
    #define lowbit(x) x & -x
    
    inline void add(int x, int v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

struct Block
{
    int l, r;
    int h[M];
    ll pre[M], suf[M];
    int tt;

    inline void build()
    {
        tt = 0;
        for(register int i = l; i <= r; i ++ ) h[++ tt] = i;
        sort(h + 1, h + tt + 1, [](int x, int y){
            return a[x] < a[y];
        });

        for(register int i = l; i <= r; i ++ )
        {
            if(i ^ l) pre[i - l + 1] = pre[i - 1 - l + 1];
            pre[i - l + 1] += bit.query(n) - bit.query(a[i]);
            bit.add(a[i], 1);
        }

        for(register int i = l; i <= r; i ++ ) bit.add(a[i], -1);
        
        for(register int i = r; i >= l; i -- )
        {
            if(i ^ r) suf[i - l + 1] = suf[i + 1 - l + 1];
            suf[i - l + 1] += bit.query(a[i]);
            bit.add(a[i], 1);
        }

        for(register int i = l; i <= r; i ++ ) bit.add(a[i], -1);
    }

    inline void get(int L, int R, int to[], int &len)
    {
        len = 0;
        for(register int i = 1; i <= tt; i ++ )
            if(L <= h[i] && h[i] <= R)
                to[++ len] = a[h[i]];
    }
}B[M];

int tmp1[N], tmp2[N];
inline ll calc(int Lb, int Rb)
{
    ll res = 0;
    int tt1 = 0, tt2 = 0;
    B[Lb].get(B[Lb].l, B[Lb].r, tmp1, tt1);
    B[Rb].get(B[Rb].l, B[Rb].r, tmp2, tt2);
    // for(int i = 1; i <= tt1; i ++ ) cout << tmp1[i] << ' ';
    // puts("");
    // for(int i = 1; i <= tt2; i ++ ) cout << tmp2[i] << ' ';
    // puts("");
    register int i = 1, j = 1;
    while(i <= tt1 && j <= tt2)
    {
        if(tmp1[i] <= tmp2[j]) i ++;
        else res += tt1 - i + 1, j ++;
    }
    return res;
}

inline ll calc2(int l, int r)
{
    ll res = 0;
    int tt1, tt2;
    B[pos[l]].get(l, r, tmp1, tt1);
    B[pos[r]].get(l, r, tmp2, tt2);
    register int i = 1, j = 1;
    while(i <= tt1 && j <= tt2)
    {
        if(tmp1[i] <= tmp2[j]) i ++;
        else res += tt1 - i + 1, j ++;
    }
    return res;
}

inline ll calc3(int l, int r)
{
    ll res = 0;
    int tt1, tt2;
    B[pos[l]].get(B[pos[l]].l, l - 1, tmp1, tt1);
    B[pos[l]].get(l, r, tmp2, tt2);
    register int i = 1, j = 1;
    while(i <= tt1 && j <= tt2)
    {
        if(tmp1[i] <= tmp2[j]) i ++;
        else res += tt1 - i + 1, j ++;
    }
    return res;
}

inline ll query(int l, int r)
{
    if(pos[l] == pos[r])
    {
        ll res = 0;
        res += B[pos[l]].pre[r - B[pos[l]].l + 1] - B[pos[l]].pre[l - B[pos[l]].l];
        res -= calc3(l, r);
        return res;
    }
    else if(pos[l] + 1 == pos[r])
    {
        ll res = 0;
        res += B[pos[l]].suf[l - B[pos[l]].l + 1];
        res += B[pos[r]].pre[r - B[pos[r]].l + 1];
        res += calc2(l, r);
        return res;
    }
    else
    {
        ll res = s[pos[l] + 1][pos[r] - 1];
        res += B[pos[l]].suf[l - B[pos[l]].l + 1];
        res += B[pos[r]].pre[r - B[pos[r]].l + 1];
        res += calc2(l, r);

        for(int i = pos[l] + 1; i < pos[r]; i ++ )
            res += f[i][B[pos[l] + 1].l - 1] - f[i][l - 1] + f[i][r] - f[i][B[pos[r] - 1].r];
        return res;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    // in >> n; in >> m;
    n = read(), m = read();
    BL = sqrt(n), T = n / BL;
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        b[i] = {a[i], i};
    }

    for(register int i = 1; i <= T; i ++ )
        B[i].l = (i - 1) * BL + 1, B[i].r = i * BL;
    
    if(B[T].r != n)
    {
        T ++;
        B[T].l = B[T - 1].r + 1;
        B[T].r = n;
    }

    for(register int i = 1; i <= T; i ++ )
    {
        for(register int j = B[i].l; j <= B[i].r; j ++ )
            pos[j] = i;
        B[i].build();
        s[i][i] = B[i].pre[B[i].tt];
    }

    sort(b + 1, b + n + 1);
    for(int i = 1; i <= T; i ++ )
    {
        int k = B[i].l;
        for(int j = 1; j <= n; j ++ )
        {
            while(k <= B[i].r && b[j].first > a[B[i].h[k - B[i].l + 1]])
                k ++;
            if(b[j].second < B[i].l)
                f[i][b[j].second] = k - B[i].l;
            else if(b[j].second > B[i].r)
                f[i][b[j].second] = B[i].r - k   + 1;
        }
    }

    for(int i = 1; i <= T; i ++ )
        for(int j = 2; j <= n; j ++ )
            f[i][j] += f[i][j - 1];

    // for(int i = 1; i <= n; i ++ ) cout << pos[i] << ' ';
    // puts("");

    // for(int i = 1; i <= n; i ++ )
    // {
    //     for(int j = 1; j <= T; j ++ )
    //         printf("%lld ", f[j][i]);
    //     puts("");
    // }

    // cout << calc2(2, 8) << endl;

    for(register int len = 2; len <= T; len ++ )
    {
        for(register int l = 1; l <= T; l ++ )
        {
            int r = l + len - 1;
            if(r > T) break;
            s[l][r] = s[l + 1][r] + s[l][r - 1] - s[l + 1][r - 1];
            s[l][r] += f[r][B[l].r] - f[r][B[l].l - 1];
        }
    }

    // cout << calc2(2, 5) << endl;

    // for(int i = 1; i <= T; i ++ )
    // {
    //     for(int j = i; j <= T; j ++ )
    //         cout << s[i][j] << ' ';
    //     puts("");
    // }

    // for(int i = 1; i <= T; i ++ )
    // {
    //     for(int j = 1; j <= n; j ++ )
    //         printf("%d ", o[i][j]);
    //     puts("");
    // }

    while(m -- )
    {
        ll l, r;
        l = read(), r = read();
        // l ^= lastans, r ^= lastans;
        if(l < 0 || l > n || r < 0 || r > n || l > r)
        {
            puts("0");
            lastans = 0;
            continue;
        }
        lastans = query(l, r);
        printf("%lld\n", lastans);
    }
    
    return 0;
}
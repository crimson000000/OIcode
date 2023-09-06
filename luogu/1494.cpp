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
const int N = 1e5 + 10;

int n, m;
int a[N];
int pos[N];

struct Q
{
    int op, l, r;
    bool operator < (const Q& q)
    {
        if(pos[l] != pos[q.l]) return pos[l] < pos[q.l];
        return pos[r] < pos[q.r]; 
    }
}q[N];

struct fraction
{
    ll up, down;

    ll gcd(ll a, ll b)
    {
        if(!b) return a;
        return gcd(b, a % b);
    }

    void divide()
    {
        ll d = gcd(up, down);
        up /= d, down /= d;
    }

    void print()
    {
        printf("%lld/%lld\n", up, down);
    }

    fraction operator + (const fraction& a)
    {
        fraction ret;
        ret.down = down * a.down;
        ret.up = up * a.down + a.up * down;
        ret.divide();
        return ret;
    }

    fraction operator - (const fraction& a)
    {
        fraction res;
        res.down = down * a.down;
        res.up = up * a.down - a.up * down;
        res.divide();
        return res;
    }

    fraction operator * (const fraction& a)
    {
        fraction res;
        res.down = a.down * down;
        res.up = a.up * up;
        res.divide();
        return res;
    }

    fraction operator / (const fraction& a)
    {
        fraction res;
        res.down = a.up * down;
        res.up = a.down * up;
        res.divide();
        return res;
    }
}ans[N];

ll cnt;
int num[N];

void add(int pos)
{
    cnt += num[a[pos]];
    num[a[pos]] ++;
}

void sub(int pos)
{
    num[a[pos]] --;
    cnt -= num[a[pos]];
}

ll C(ll n, ll m)
{
    ll res = 1;
    for(int i = n - m + 1; i <= n; i ++ ) res *= i;
    for(int i = 1; i <= m; i ++ ) res /= i;
    return res;
}


int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d", &n, &m);
    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ )
    {
        pos[i] = (i - 1) / _;
        scanf("%d", &a[i]);
    }
    
    for(int i = 1; i <= m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }

    sort(q + 1, q + m + 1);

    int L = 1, R = 0;
    for(int i = 1; i <= m; i ++ )
    {
        while(R < q[i].r) add(++ R);
        while(L > q[i].l) add(-- L);
        while(R > q[i].r) sub(R --);
        while(L < q[i].l) sub(L ++);
        if(q[i].l == q[i].r) ans[q[i].op] = {0, 1};
        else
        {
            ans[q[i].op] = {cnt, C(q[i].r - q[i].l + 1, 2)};
            ans[q[i].op].divide();
        }
    }

    for(int i = 1; i <= m; i ++ )
    {
        ans[i].print();
    }
    
    return 0;
}

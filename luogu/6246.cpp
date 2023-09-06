#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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
ll f[N], cnt[N];
ll a[N], s[N];
int n, k;

ll calc(int l, int r)
{
    int mid = l + r + 1 >> 1;
    return a[mid] * (mid - l + 1) - (s[mid] - s[l - 1]) + (s[r] - s[mid]) - a[mid] * (r - mid);
}

// calc j -> i value
ll w(int j, int i)
{
    return f[j] + calc(j + 1, i);
}

struct node
{
    int l, r, j;
}q[N];
int tt, hh;

int find(int i)
{
    int l = q[tt].l, r = q[tt].r + 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(w(q[tt].j, mid) > w(i, mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

void insert(int i)
{
    while(hh <= tt && w(q[tt].j, q[tt].l) > w(i, q[tt].l)) tt --;
    if(hh > tt)
    {
        q[++ tt].l = i;
        q[tt].r = n;
        q[tt].j = i;
        return;
    }

    int pos = find(i);
    if(pos > n) return;
    q[tt].r = pos - 1;
    tt ++;
    q[tt].l = pos;
    q[tt].r = n;
    q[tt].j = i;
    return;
}

bool check(ll mid)
{
    f[0] = 0, cnt[0] = 0;
    hh = 0, tt = -1;
    q[++ tt] = {1, n, 0};

    for(int i = 1; i <= n; i ++ )
    {
        while(hh <= tt && q[hh].r < i) hh ++;
        q[hh].l = i;
        f[i] = w(q[hh].j, i) + mid;
        cnt[i] = cnt[q[hh].j] + 1;
        insert(i);
    }

    return cnt[n] >= k;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        s[i] = s[i - 1] + a[i];
    }

    ll l = 0, r = 1e9;
    while(l < r)
    {
        ll mid = l + r >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }

    check(l);
    cout << f[n] - k * l << endl;

    return 0;
}

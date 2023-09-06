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
ll a[N], b[N];
ll suma[N], sumb[N];
int n;
map<ll, PII> mp;
int l1, r1, l2, r2;
int op;

void print()
{
    if(!op)
    {
        printf("%d\n", r1 - l1 + 1);
        for(int i = l1; i <= r1; i ++ ) printf("%d ", i);
        puts("");
        printf("%d\n", r2 - l2 + 1);
        for(int i = l2; i <= r2; i ++ ) printf("%d ", i);
        puts("");
    }
    else
    {
        printf("%d\n", r2 - l2 + 1);
        for(int i = l2; i <= r2; i ++ ) printf("%d ", i);
        puts("");
        printf("%d\n", r1 - l1 + 1);
        for(int i = l1; i <= r1; i ++ ) printf("%d ", i);
        puts("");
    }
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
        a[i] = read();
        suma[i] = suma[i - 1] + a[i];
    }

    for(int i = 1; i <= n; i ++ )
    {
        b[i] = read();
        sumb[i] = sumb[i - 1] + b[i];
    }

    if(suma[n] > sumb[n])
    {
        swap(a, b);
        swap(suma, sumb);
        op = 1;
    }

    for(int i = 1; i <= n; i ++ )
    {
        ll pos = upper_bound(suma + 1, suma + n + 1, sumb[i]) - suma - 1;
        if(suma[pos] == sumb[i])
        {
            l1 = 1, l2 = 1;
            r1 = pos, r2 = i;
            print();
            return 0;
        }
        ll x = sumb[i] - suma[pos];
        if(mp.count(x))
        {
            l1 = mp[x].first + 1, r1 = pos;
            l2 = mp[x].second + 1, r2 = i;
            print();
            return 0;
        }
        else mp[x] = {pos, i};
    }

    return 0;
}
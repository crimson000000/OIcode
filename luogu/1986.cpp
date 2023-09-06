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
struct seg
{
    int l, r, c;
    bool operator < (const seg& a) const
    {
        return r < a.r;
    }
}a[N];
int n, m, sum;
bitset<N> st;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read(), c = read();
        a[i] = {x, y, c};
    }

    sort(a + 1, a + m + 1);

    for(int i = 1; i <= m; i ++ )
    {
        int s = 0;
        for(int j = a[i].l; j <= a[i].r; j ++ )
            if(st[j])
                s ++;
        for(int j = a[i].r; j >= a[i].l; j -- )
        {
            if(s >= a[i].c) break;
            if(!st[j])
            {
                st[j] = true;
                s ++;
                sum ++;
            }
        }
    }

    cout << sum << endl;

    return 0;
}
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
int n, ans;

struct seg
{
    int l, r, id;
};
seg q[N];
int hh, tt = -1;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    
    for(int i = 1; i <= n; i ++ )
    {
        int l = read(), r = read();
        while(hh <= tt && q[hh].l > r) hh ++;
        if(hh <= tt) ans = max(ans, i - q[hh].id + 1);

        int tmp = i;
        while(hh <= tt && q[tt].l < l)
        {
            tmp = q[tt].id;
            tt --;
        }
        q[++ tt] = {l, r, tmp};
    }

    cout << max(ans, 1) << endl;

    return 0;
}
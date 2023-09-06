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
char s[N];
int cnt[100];
int cnt1, cnt2;
int n, k;

bool check(int mid)
{
    if(mid & 1)
    {
        int y = k;
        int tmp1 = cnt1, tmp2 = cnt2;
        while(y -- )
        {
            if(tmp1) 
            {
                tmp2 -= (mid - 1) / 2;
                tmp1 --;
            }
            else
            {
                tmp1 += 2;
                tmp2 --;
                tmp2 -= (mid - 1) / 2;
                tmp1 --;
            }
            if(tmp2 < 0) return false;
        }
        return true;
    }
    else
    {
        if(cnt2 < k * mid / 2) return false;
        return true;
    }
}

void solve()
{
    memset(cnt, 0, sizeof cnt);
    cnt1 = cnt2 = 0;
    n = read(), k = read();
    scanf("%s", s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        int c = s[i] - 'a';
        cnt[c] ++;
        if(cnt[c] == 2) cnt[c] = 0, cnt1 --, cnt2 ++;
        else cnt1 ++;
    }

    cnt1 = min(cnt1, cnt2);

    int l = 1, r = n / k;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1; 
    }
    cout << l << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}
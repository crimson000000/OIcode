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
int a[N], cnt[N], olda[N];
vector<int> nums;
int n;

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
        nums.push_back(a[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin();
        cnt[a[i]] ++;
        olda[i] = a[i];
    }

    for(int i = 1; i <= n; i ++ ) cnt[i] += cnt[i - 1];
    for(int i = n; i; i -- ) a[cnt[olda[i]] -- ] = olda[i];
    for(int i = 1; i <= n; i ++ ) 
        printf("%d ", nums[a[i]]);

    return 0;
}

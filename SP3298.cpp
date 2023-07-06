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

int pow10(int x)
{
    int res = 1;
    while(x -- ) res *= 10;
    return res;
}

int getnum(vector<int> nums, int l, int r)
{
    int res = 0;
    for(int i = l; i >= r; i -- )
        res = res * 10 + nums[i];
    return res;
}

int dp(int n, int x)
{
    if(!n) return 0;
    vector<int> nums;

    while(n) nums.push_back(n % 10), n /= 10;
    int res = 0;
    n = nums.size() - 1;

    for(int i = n - !x; i >= 0; i -- )
    {
        int t = nums[i];
        if(i < n)
        {
            res += getnum(nums, n, i + 1) * pow10(i);
            if(!x) res -= pow10(i);
        }
        
        if(t == x) res += getnum(nums, i - 1, 0) + 1;
        else if(t > x) res += pow10(i);
    }

    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int l, r;
    while(scanf("%d%d", &l, &r), l | r)
    {
        if(l > r) swap(l, r);
        for(int i = 0; i <= 9; i ++ )
            cout << dp(r, i) - dp(l - 1, i) << ' ';
        puts("");
    }
    
    return 0;
}

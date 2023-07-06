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

const int N = 64;
ll x;
vector<int> nums;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T;
    cin >> T;
    while(T -- )
    {
        cin >> x;
        ll ans = 1;
        nums.clear();

        while(x) nums.push_back(x % 3), x /= 3;
        for(int i = 0; i < nums.size(); i ++ )
        {
            int t = nums[i];
            if(i == 0 && t == 2)
            {
                ans = 0;
                break;
            }
            
            if(i != 0 && t == 1) ans *= 2;
        }
        cout << ans << endl;
    }
    
    return 0;
}

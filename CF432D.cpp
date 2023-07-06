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

const int N = 2e5 + 10;
int ne[N];
vector<int> ans;
int dp[N];
char s[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);

    int n = strlen(s + 1);
    for(int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
    }

    for(int i = ne[n]; i; i = ne[i]) ans.push_back(i);
    ans.push_back(n);

    for(int i = n; i >= 1; i -- )
    {
        dp[i] ++;
        dp[ne[i]] += dp[i];
    }
    
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i ++ )
        cout << ans[i] << " " << dp[ans[i]] << endl;
    
    return 0;
}

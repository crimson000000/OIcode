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

const int N = 1e5 + 10;
char s[N];
int a[N];
vector<int> ans;
int k;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    k = read();
    int n = strlen(s + 1);
    int rest = n - k;

    for(int i = 1; i <= n; i ++ )
        a[i] = s[i] - '0';
    
    int lastl = 0;
    while(rest - ans.size())
    {
        int minn = 1e9;
        for(int i = lastl + 1; i <= n - rest + ans.size() + 1; i ++ )
            if(a[i] < minn)
                minn = a[i], lastl = i;
        ans.push_back(minn);
    }

    while(ans[0] == 0 && ans.size() > 1) ans.erase(ans.begin());

    for(auto t : ans)
        cout << t;

    return 0;
}

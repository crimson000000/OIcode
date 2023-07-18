#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 2e6 + 10;
string s;
int n, len;
string ans;
int ne[N];

inline int kmp(string s)
{
    s = ' ' + s;
    int n = s.size();
    ne[1] = 0;
    for(int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
    }
    return ne[n];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin.tie(0);
    ios::sync_with_stdio(false);
    
    cin >> n;
    cin >> ans;
    for(int i = 2; i <= n; i ++ )
    {
        cin >> s;
        int len = min(ans.size(), s.size());
        string ss = s + "*)%#*)%(@&#)%()" + ans.substr(ans.size() - len, len);
        kmp(ss);
        for(int j = ne[ss.size()]; j < s.size(); j ++ ) ans += s[j];
    }

    cout << ans << endl;

    return 0;
}
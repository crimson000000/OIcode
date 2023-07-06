#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int ne[N];
string s, ans;
int n;

void kmp(string s)
{
    ne[1] = 0;
    s = ' ' + s;
    int len = s.size();
    for(int i = 2, j = 0; i <= len; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
    }
}

int main()
{
    scanf("%d", &n);
    cin >> ans;
    for(int i = 1; i < n; i ++ )
    {
        cin >> s;
        int len = min(ans.size(), s.size());
        string ss = s + "哼哼哼，啊啊啊啊啊啊啊"+ ans.substr(ans.size() - len, len);
        kmp(ss);
        for(int j = ne[ss.size()]; j < s.size(); j ++ ) ans += s[j];
    }        
    cout << ans << endl;
}
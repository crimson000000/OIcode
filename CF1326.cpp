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

int T;
const int N = 4e6 + 10;
string s, t;
string rev, ans;
string s1, s2;
int ne1[N], ne2[N];

bool check(string s)
{
    for(int i = 0; i < s.size(); i ++ )
    {
        if(s[i] != s[s.size() - i - 1]) return false;
    }
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while(T -- )
    {
        cin >> s;int len = s.size();
        for(int i = 0; i <= len * 2; i ++ ) ne1[i] = ne2[i] = 0;
        
        if(check(s))
        {
            cout << s << endl;
            continue;
        }

        
        int p = 0, q = len - 1;
        while(s[p] == s[q]) p ++, q --;

        t = s.substr(0, p);
        s = s.substr(p, q - p + 1);
        rev = s;
        reverse(rev.begin(), rev.end());

        s1 = s + '*' + rev, s2 = rev + '*' + s;
        for(int i = 2, j = 0; i <= s1.size(); i ++ )
        {
            while(j && s1[i - 1] != s1[j]) j = ne1[j];
            if(s1[i - 1] == s1[j]) j ++ ;
            ne1[i] = j;
        }

        for(int i = 2, j = 0; i <= s2.size(); i ++ )
        {
            while(j && s2[i - 1] != s2[j]) j = ne2[j];
            if(s2[i - 1] == s2[j]) j ++ ;
            ne2[i] = j;
        }

        if(ne1[s1.size()] > ne2[s2.size()])
        {
            ans = s1.substr(0, ne1[s1.size()]);
        }
        else
        {
            ans = s2.substr(0, ne2[s2.size()]);
        }

        cout << t << ans;
        reverse(t.begin(), t.end());
        cout << t << endl;
    }
   
    return 0;
}

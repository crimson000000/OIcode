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

string a, b;
string s;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> s;

    for(int i = 0; i < s.size(); i ++ )
    {
        if(s[i] == 'X') a[i] = '3', b[i] = '2';
        if(s[i] == 'Y') a[i] = '2', b[i] = '3';
        if(s[i] == 'Z') a[i] = '0', b[i] = '0';
    }

    cout << a << endl << b << endl;
    
    return 0;
}

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

int m, s, t;
int s1, s2;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> m >> s >> t;

    for(int i = 1; i <= t; i ++ )
    {
        s1 += 17;
        if(m >= 10) s2 += 60, m -= 10;
        else m += 4;
        if(s2 > s1) s1 = s2;

        if(s1 >= s) 
        {
            puts("Yes");
            cout << i << endl;
            return 0;
        }
    }

    cout << "No" << endl << s1 << endl;

    return 0;
}

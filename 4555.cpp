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

const int N = 5e5 + 10;
int l[N], r[N];
char t[N], s[N];
int f[N];

void manacher(int len)
{
    s[0] = '$', s[1] = '#';
    int cnt = 1;
    for(int i = 1; i <= len; i ++ ) 
    {
        s[++ cnt] = t[i];
        s[++ cnt] = '#';
    }
    len = len << 1 | 1, s[len + 1] = '!';
    int mid = 0, mr = 1;
    for(int i = 1; i <= len; i ++ )
    {
        if(i >= mr) f[i] = 1;
        else f[i] = min(mr - i, f[2 * mid - i]);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++ ;
        if(i + f[i] > mr) mr = i + f[i], mid = i;
        r[i - f[i] + 1] = max(r[i - f[i] + 1], f[i] - 1);
        l[i + f[i] - 1] = max(l[i + f[i] - 1], f[i] - 1);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", t + 1);
    int len = strlen(t + 1);
    manacher(len);
    len = len * 2 + 2;
    for(int i = 1; i <= len; i += 2) r[i] = max(r[i], r[i - 2] - 2);
    for(int i = len; i >= 1; i -= 2) l[i] = max(l[i], l[i + 2] - 2);

    int ans = 0;
    for(int i = 1; i <= len; i += 2)
    {
        if(l[i] && r[i])
            ans = max(ans, l[i] + r[i]);        
    }

    cout << ans << endl;
   
    return 0;
}

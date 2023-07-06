#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N], t[N];
int ne[N], f[N];
int st[N], tt;
int ls, lt;

int main()
{
    scanf("%s%s", s + 1, t + 1);
    ls = strlen(s + 1), lt = strlen(t + 1);
    for(int i = 2, j = 0; i <= lt; i ++ )
    {
        while(t[j + 1] != t[i] && j) j = ne[j];
        if(t[j + 1] == t[i]) j ++;
        ne[i] = j;
    }
    for(int i = 1, j = 0; i <= ls; i ++ )
    {
        while(j && s[i] != t[j + 1]) j = ne[j];
        if(s[i] == t[j + 1]) j ++;
        f[i] = j;
        st[++ tt] = i;
        if(j == lt)
        {
            tt -= lt, j = f[st[tt]];
        }
    }
    for(int i = 1; i <= tt; i ++ )
    {
        cout << s[st[i]];
    }
    return 0;
}
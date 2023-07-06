#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
string s;
int n;

int main()
{
    scanf("%d", &n);

    bool flag = false;
    char ch;
    for(int i = 0; i < n; i ++ )
    {
        ch = getchar();
        if(ch == 'n') flag = true;
        if(ch == 'a' && flag)
        {
            s += "nya";
            i ++;
            flag = false;
            continue;
        }
        s += ch;
    }
    cout << s << endl;
}
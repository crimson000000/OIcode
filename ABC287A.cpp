#include <bits/stdc++.h>
using namespace std;
string s;
int n;
int f, a;

int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++ )
    {
        cin >> s;
        if(s[0] == 'F') f ++;
        else a ++ ;
    }
    if(f > a) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
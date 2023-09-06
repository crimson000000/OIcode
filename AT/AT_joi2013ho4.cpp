#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N];
bool st[N];
int onum, inum;
int n;

bool check(int x)
{
    int cnti = 0, cnto = 0, cnt = 0;
    for(int i = n; i > 0; i -- )
    {
        if(s[i] == 'J' && cnto) cnto --, cnt ++;
        if(s[i] == 'O' && cnti) cnti --, cnto ++;
        if(s[i] == 'I')
        {
            if(cnt + cnto + cnti < x) cnti ++;
            else if(cnto) cnt ++, cnto --;
        }
    }
    return cnt >= x;
}

int main()
{
    scanf("%d%s", &n, s + 1);

    int l = 0, r = n / 3;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << endl;
    return 0;
}
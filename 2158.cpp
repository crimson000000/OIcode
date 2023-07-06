#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
ll phi[N];
int n, cnt;

int main()
{
    cin >> n;
    phi[1] = 1;
    if(n == 1) 
    {
        cout << 0 << endl;
        return 0;    
    }
    for(int i = 1; i <= n; i ++ ) phi[i] = i;
    for(int i = 2; i <= n; i ++ )
    {
        if(phi[i] == i)
        {
            for(int j = i; j <= n; j += i)
            {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    n --;
    ll sum = 0;
    for(int i = 2; i <= n; i ++ ){
        sum += phi[i];
    }
    sum = sum * 2 + 3;
    cout << sum << endl;
}
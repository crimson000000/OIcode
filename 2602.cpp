#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b;

ll pow10(int x)
{
    ll res = 1;
    while(x -- )
        res *= 10;
    return res;
}

ll get(vector<int> num, int l, int r)
{
    ll res = 0;
    for(int i = l; i >= r; i -- )
        res = res * 10 + num[i];
    return res;
}

ll count(int x, ll n)
{
    if(!n) return 0;
    vector<int> num;
    while(n) {
        num.push_back(n % 10);
        n /= 10;
    }
    n = num.size();

    ll res = 0;
    for(int i = n - 1 - !x; i >= 0; i -- )
    {
        if(i < n - 1)
        {
            res += get(num, n - 1, i + 1) * pow10(i);
            if(!x) res -= pow10(i);
        }

        if(num[i] == x) res += get(num, i - 1, 0) + 1;
        else if(num[i] > x) res += pow10(i);
    }
    return res;
}

int main()
{
    
        
            freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
            freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
       
    
    
    cin >> a >> b;

    for(int i = 0; i <= 9; i ++ )
        cout << count(i, b) - count(i, a - 1) << " ";
    puts(""); 
    return 0;
}
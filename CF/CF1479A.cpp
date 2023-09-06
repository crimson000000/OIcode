#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;
int a[N];

int main()
{
    cin >> n;
    int l = 1, r = n;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(a[mid] == 0){
            printf("? %d\n", mid);
            fflush(stdout);
            cin >> a[mid];
        }
        if(a[mid + 1] == 0){
            printf("? %d\n", mid + 1);
            fflush(stdout);
            cin >> a[mid + 1];
        }
        if(a[mid] >= a[mid + 1])
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    printf("! %d\n", l);
    return 0;
}
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

const int N = 1e6 + 10;

priority_queue<int> heap1;
priority_queue<int, vector<int>, greater<int>> heap2;
int a[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int n = read();

    a[1] = read();
    int mid = a[1];
    cout << mid << endl;

    for(int i = 2; i <= n; i ++ )
    {
        a[i] = read();
        if(a[i] > mid) heap2.push(a[i]);
        else heap1.push(a[i]);
        
        if(i % 2 == 1)
        {
            while(heap1.size() != heap2.size())
            {
                if(heap1.size() > heap2.size())
                {
                    heap2.push(mid);
                    mid = heap1.top();
                    heap1.pop();
                }
                else
                {
                    heap1.push(mid);
                    mid = heap2.top();
                    heap2.pop();
                }
            }
            cout << mid << endl;
        }
    }
    
    return 0;
}

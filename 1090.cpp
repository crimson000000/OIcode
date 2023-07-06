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

priority_queue<int, vector<int>, greater<int> > heap;
const int N = 1e6 + 10;
int a[N];
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        heap.push(a[i]);
    }

    int ans = 0;
    while(heap.size() != 1)
    {
        int a1 = heap.top();
        heap.pop();
        int a2 = heap.top();
        heap.pop();
        ans += a1 + a2;
        heap.push(a1 + a2);
    }

    cout << ans << endl;
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int r[N], h[N], bests[N], bestv[N];
int n, m, ans = 1 << 30;

void dfs(int depth, int s, int v, int lr, int lh)
{
    //x:层数 nowans:最优剪枝
    if(depth == 0)
    {
        if(v == n && s < ans)
            ans = s;
        return;
    }
    if(s + bests[depth - 1] > ans || v + bests[depth - 1] > n) return;
    if(2 * (n - v) / lr + s > ans) return;
    

    for(int i = lr - 1; i >= depth; i --)
    {
        if(depth == m) s = i * i;
        int h = min((n - v - bestv[depth - 1]) / (i * i), lh - 1);
        for(int j = h; j >= depth; j -- )
        {
            dfs(depth - 1, s + 2 * i * j, v + i * i * j, i, j);
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= 15; i ++ )
    {
        bests[i] = bests[i - 1] + 2 * i * i;
        bestv[i] = bestv[i - 1] + i * i * i;
    }

    dfs(m, 0, 0, n + 1, n + 1);

    cout << ans << endl;
}
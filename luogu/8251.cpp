#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 5e5 + 10;
int ne[N][22];
int n, q;
struct ele
{
    int a, b, id;
}p[N];
stack<ele> stk;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), q = read();
    for(int i = 1; i <= n; i ++ ) p[i].a = read();
    for(int i = 1; i <= n; i ++ ) p[i].b = read();
    for(int i = 1; i <= n; i ++ ) p[i].id = i;

    for(int i = 1; i <= n; i ++ )
    {
        while(stk.size() && !(stk.top().a != p[i].a && stk.top().b > p[i].b))
        {
            ne[stk.top().id][0] = i;
            stk.pop();
        }
        stk.push(p[i]);
    }

    for(int i = 1; i <= 20; i ++ )
        for(int j = 1; j <= n; j ++ )
            ne[j][i] = ne[ne[j][i - 1]][i - 1];
    
    while(q -- )
    {
        int l = read(), r = read();
        int res = 0;
        for(int i = 20; i >= 0; i -- )
        {
            if(ne[l][i] && ne[l][i] <= r)
            {
                l = ne[l][i];
                res += 1 << i;
            }
        }
        printf("%d\n", res + 1);
    }

    return 0;
}

/*
显然弹到停止的条件是 ai=aj 或者 bi>=bj
如果没了第一个条件就是看左边有多少数比它小，为 0 的就是成功的
这个条件其实有了 ai 也还适用
但是多了个前面没有编号相同的
首先我们只需要维护这个区间内第一个出现的 ai

不行
相同的 ai 可能会被别的 ai 弹掉，怎么办
能不能倍增
类似 ST 表，f[i][j] 为 i 后面 2^j 个元素加进去后的成功元素
应该不可行，不可加
如果直接存里面放了啥的话单调上升就能给卡爆空间

先看下特殊性质
b 单调递减的性质应该好维护，每个数看左边有没有相同的，也就是区间数颜色了，二维数点
a 不同的性质应该也还好，思考一下

在这里条件就成了：L <= j < i <= R 且 b_i<b_j 的情况，能离线下来吗
莫队+kdt 必然不行，直接n方了

看看题解吧
还真是倍增啊
牛逼
*/
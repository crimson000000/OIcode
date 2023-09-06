#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int N = 250010;
int a[N]; 
PII fmaxn[N][21], fmi[N][21];
int lg2[N];
int n;

void ST_pre()
{
    for(int i = 1; i <= n; i ++ ){ 
        fmaxn[i][0].first = fmi[i][0].first = a[i];
        fmaxn[i][0].second = fmi[i][0].second = i;
    }
    for(int i = 1; i < 21; i ++ )
        for(int j = 1; j + (1 << i - 1) <= n; j ++ ){
            fmaxn[j][i] = max(fmaxn[j][i - 1], fmaxn[j + (1 << (i - 1))][i - 1]);
            fmi[j][i] = min(fmi[j][i - 1], fmi[j + (1 << (i - 1))][i - 1]);
        }
}

PII getmax(int l, int r)
{
    int t = log2(r - l + 1);
    return max(fmaxn[l][t], fmaxn[r - (1 << t) + 1][t]);
}

PII getmin(int l, int r)
{
    int t = log2(r - l + 1);
    return min(fmi[l][t], fmi[r - (1 << t) + 1][t]);
}

int solve(int l, int r)
{
    if(l >= r) return 0; 

    int pos1 = getmax(l, r).second, pos2 = getmin(l, r).second;
    if(pos1 > pos2) swap(pos1, pos2);
    return (1 + solve(l, pos1) + solve(pos2, r));
}

int main()
{
    int T;
    scanf("%d", &T);

/*    lg2[0] = 0;
    for(int i = 1; i <= N; i ++ )
    {
        lg2[i] = lg2[i - 1];
        if((i >> (lg2[i] + 1)) & 1) lg2[i] ++;
    }
*/
    while(T -- )
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++ ) {
            scanf("%d", &a[i]);
        }
        ST_pre();

        cout << solve(1, n) << endl;
    }
    return 0;
}
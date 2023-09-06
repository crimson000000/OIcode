#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

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

const int N = 1e6 + 10;
int a[N];
int n, m, p;

int b[N], cnt[N];
void count_sort(int *begin, int *end)
{
    memset(cnt, 0, (n + 1) * sizeof(int));
    for(int *it = begin; it < end; it ++ ) cnt[*it] ++;
    for(int i = 1; i <= n; i ++ ) cnt[i] += cnt[i - 1];
    for(int *i = end - 1; i >= begin; i -- ) b[(cnt[*i] -- )] = *i;
    for(int i = 1; i <= end - begin; i ++ )
        *(begin + i - 1) = b[i];
}

int main()
{
	#ifdef LOCAL
		freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
		freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
	#endif

	n = read(), m = read();

	for(int i = 1; i <= n; i ++ ) a[i] = read();
	for(int i = 1; i <= m; i ++ )
	{
		int op = read(), l = read(), r = read();
        count_sort(a + l, a + r + 1);
        if(op == 1) reverse(a + l, a + r + 1);
        // for(int j = 1; j <= n; j ++ ) cout << a[j] << ' ';
        // puts("");
	}
	
    int k = read();
    cout << a[k] << endl;

	return 0;
}
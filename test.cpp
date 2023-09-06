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

int main()
{
	#ifdef LOCAL
		freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
		freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
	#endif

	double ans = 0;
	for(int i = 1; i <= 100000000; i ++ )
	{
		ans += pow(1.0001, i);
	}

	cout << ans << endl;

	return 0;
}
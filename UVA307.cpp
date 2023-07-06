#include <bits/stdc++.h>
using namespace std;
const int N = 70;
int a[N], v[N];
int n, sum, val, len, cnt;

bool dfs(int st, int now, int last) 
{
	if (st >= cnt)
		return true;
	if (now == len)
		return dfs(st + 1, 0, 1);

	int fail = 0;
	for (int i = last; i <= n; i ++ ) {
		if (!v[i] && fail != a[i] && now + a[i] <= len) 
        {
			v[i] = 1;
			if (dfs(st, now + a[i], i + 1))
				return true;

			v[i] = 0;
			fail = a[i];
			if (now == 0 || now + a[i] == len)
				return false;
		}
	}

	return false;
}

int main() {
	while(scanf("%d", &n), n)
    {
        sum = 0;
        val = 0;
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; i ++ ) 
        {
            scanf("%d", &a[i]);
            sum += a[i];
            val = max(val, a[i]);
        }

        sort(a + 1, a + n + 1);
        reverse(a + 1, a + n + 1);

        for (len = val; len <= sum; len ++ ) 
        {
            if (sum % len == 0) 
            {
                cnt = sum / len;
                memset(v, 0, sizeof v);
                if (dfs(1, 0, 1))
                    break;
            }
        }

        cout << len << endl;
    }
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int a[N], rev[N];
ll n, cnt;

void merge(int q[], int l, int r) {
	if (l >= r)
		return;
	int mid = l + r >> 1;
	merge(q, l, mid);
	merge(q, mid + 1, r);
	int i = l, j = mid + 1, k = 0;
	while (i < mid + 1 && j < r + 1) {
		if (a[i] > a[j]) {
			cnt += mid - i + 1;
			rev[k ++] = a[j ++];
		} else
			rev[k ++] = a[i ++];
	}
	while (i < mid + 1) {

		rev[k ++] = a[i ++];
	}
	while (j < r + 1)
		rev[k ++] = a[j ++];

	for (int i = l, j = 0; i <= r; i ++)
		q[i] = rev[j ++];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 100000; i ++) a[i] = i;
    for(int i = 0; i <=)

	merge(a, 0, n - 1);
	cout << cnt << endl;
}
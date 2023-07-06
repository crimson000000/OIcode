#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
double a, b, c, d;

double f(double x) {
	return abs(log(x - 1) / log(3)) - pow(1 / 3, x) - 1;
}

int main() {
	int s = 0;
	for (int i = -100; i <= 100; i = i + 1) {
		double l = i, r = i + 1;
		double fl = f(l), fr = f(r);
		if (!fl) {
			printf("%.6lf ", l);
			s ++;
		}

		if (fl * fr < 0) {
			while (r - l > eps) {

				double mid = (l + r) / 2;
				if (f(r) * f(mid) <= 0)
					l = mid;
				else
					r = mid;
			}
			s ++;
			printf("%.6lf ", l);

		}
		
	}


	return 0;
}

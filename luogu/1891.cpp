#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b){
	return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b){
	return a / gcd(a, b) * b;
}

int main(){
	
	ll last = 1;
	for(ll i = 1; i <= 1000000; i ++ ){
		last = lcm(last, i);
		cout << last << " ";
		
	}
}

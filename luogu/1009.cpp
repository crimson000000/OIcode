#include<bits/stdc++.h>
using namespace std;
vector<int> add(vector<int> &A, vector<int> &B)
{
    if (A.size() < B.size()) return add(B, A);

    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i ++ )
    {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }

    if (t) C.push_back(t);
    return C;
}
vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;

    int t = 0;
    for (int i = 0; i < A.size() || t; i ++ )
    {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}
int main(){
	int n;
	cin>>n;
	vector<int> ans;
	ans.push_back(0);
	for(int i=1;i<=n;i++){
		vector<int> jie;
		jie.push_back(1);
		for(int j=1;j<=i;j++){
			jie=mul(jie,j);
		}
		ans=add(ans,jie);
	}
	for(int i=ans.size()-1;i>=0;i--) cout<<ans[i];
	return 0;
}

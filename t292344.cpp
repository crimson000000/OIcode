#include<bits/stdc++.h>
using namespace std;

vector<int> add(vector<int>&a ,vector<int>&b){
	vector<int> c;
	int t=0;
	for(int i=0;i<a.size() || i<b.size();i++){
		if(i<a.size()) t+=a[i];
		if(i<b.size()) t+=b[i];
		c.push_back(t%10);
		t/=10; 
	}
	if(t) c.push_back(1);
	return c;
}

vector<int> mul(vector<int> &a,int b){
	vector<int> c;
	int t=0;
	for(int i=0;i<a.size() || t;i++){
		if(i<a.size()) t+=a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	return c;
}


vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i ++ )
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}


int main(){
	string m;
	int n;
	cin>>m>>n;
	vector<int> M,N,one;
	for(int i=m.size()-1;i>=0;i--) M.push_back(m[i]-'0');
	
	one.push_back(1);
	auto d=mul(M,n);
	auto ans=sub(d,one);
	for(int i=ans.size()-1;i>=0;i--) cout<<ans[i]; 
	return 0;
	
}  

#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cxx __gnu_cxx
#define pbds __gnu_pbds
#define inf (INT_MAX >> 1)
#define llinf (LLONG_MAX >> 1)
#define for_0(rangeNum) for(int i = 0;i < rangeNum;i++)
#define for_1(rangeNum) for(int i = 1;i <= rangeNum;i++)
#define lc (mid << 1)
#define rc (mid << 1 | 1)
#define mid ((l + r) >> 1)
#define lg(log2Num) __lg(log2Num)
// #define int long long

using namespace std;

string s1, s2, mg;
int l1, l2, p;
int nt[2000005];

signed main(){
	cin>>s1>>s2;// 匹配 模式
	l1 = s2.size(), l2 = s1.size();
	nt[0] = 0;
	mg = " "+ s2 + "#" + s1;
	for(int i = 2;i <= l1 + l2 + 1;i++){
		int j = nt[i - 1];
		while(j >= 1 && mg[i] != mg[j + 1]){
			j = nt[j];
		}
		if(mg[i] == mg[j + 1]){
			j++;
		}
		nt[i] = j;
		if(i > l1 && nt[i] == l1){
			cout<<i - 2 * l1<<"\n";
		}
	}
	for_1(l1){
		cout<<nt[i]<<" ";
	}
	return 0;
}

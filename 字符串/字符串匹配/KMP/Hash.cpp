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
#define int unsigned long long
#define base 131

using namespace std;

char stk[1000005];
int h_stk[1000005];
int h_pow[1000005];
string s, t;
int n, m, hash_t, top, cur;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>s>>t;
	n = s.size(), m = t.size();
	h_pow[0] = 1;
	for_1(n){
		h_pow[i] = h_pow[i - 1] * base;
	}
	hash_t = 0;
	for(char c : t){
		hash_t = hash_t * base + c;
	}
	top = 0;
	for(char c : s){
		stk[++top] = c;
		h_stk[top] = h_stk[top - 1] * base + c;
		if(top >= m){
			cur = h_stk[top] - h_stk[top - m] * h_pow[m];
			if(cur == hash_t){
				top -= m;
			}
		}
	}

	for_1(top){
		cout<<stk[i];
	}

	return 0;
}
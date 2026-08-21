#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cxx __gnu_cxx
#define pbds __gnu_pbds
#define _inf 0x3f3f3f3f
#define inf (INT_MAX >> 1)
#define llinf (LLONG_MAX >> 1)
#define for_0(rangeNum) for(int i = 0;i < rangeNum;i++)
#define for_1(rangeNum) for(int i = 1;i <= rangeNum;i++)
#define lc (mid << 1)
#define rc (mid << 1 | 1)
#define mid ((l + r) >> 1)
#define lg(log2Num) __lg(log2Num)

// #define int long long
// #define int unsigned long long
#define base 131

using namespace std;

int a[205][205], t[205];
int n, m, q, p;

void floyd(int k){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(a[i][j] > a[i][k] + a[k][j]){
				a[i][j] = a[i][k] + a[k][j];
			}
		}
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	memset(a, 0x3f, sizeof(a));
	cin>>n>>m;
	for_0(n){
		a[i][i] = 0;
	}
	for_0(n){
		cin>>t[i];
	}
	for_0(m){
		int u, v, w;
		cin>>u>>v>>w;
		a[u][v] = w;
		a[v][u] = w;
	}
	cin>>q;
	for_0(q){
		int u, v, x;
		cin>>u>>v>>x;
		while(p < n && t[p] <= x){
			floyd(p++);
		}
		if(t[u] <= x && t[v] <= x){
			if(a[u][v] == _inf){
				cout<<-1<<"\n";
			}
			else{
				cout<<a[u][v]<<"\n";
			}
		}
		else{
			cout<<-1<<"\n";
		}
	}
	return 0;
}

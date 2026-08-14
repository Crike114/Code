#include<bits/stdc++.h>
#define rtt (2 * n + 1)
#define rtf (2 * n + 2)
using namespace std;

int c, t, n, m;
vector<int> fa, uk, ukl;

void init(){
	fa.clear();
	uk.clear();
	ukl.clear();
	fa.resize(2 * n + 5);
	uk.resize(2 * n + 5);
	for(int i = 1;i <= fa.size() - 1;i++){
		fa[i] = i;
	}
}
int find(int u){
	if(fa[u] == u) return u;
	return fa[u] = find(fa[u]);
}
void unite(int u, int v){
	int rtu = find(u), rtv = find(v);
	if(rtu == rtv){
		return;
	}
	fa[rtu] = rtv;
	if(uk[rtu] == 1){
		uk[rtv] = 1;
	}
}

void process(){
	cin>>c>>t;
	while(t--){
		cin>>n>>m;
		init();

		vector<int> src(n+1), neg(n+1);
		for(int i = 1;i <= n;i++){
			src[i] = i + 2;
			neg[i] = 0;
		}
		for(int k = 0;k < m;k++){
			char op;
			cin>>op;
			if(op == 'T' || op == 'F' || op == 'U'){
				int i;
				cin>>i;
				if(op == 'T'){
					src[i]=0;
					neg[i]=0;
				}
				else if(op == 'F'){
					src[i]=1;
					neg[i]=0;
				}
				else{
					src[i]=2;
					neg[i]=0;
				}
			}
			else if(op == '+'){
				int i, j;
				cin>>i>>j;
				src[i] = src[j];
				neg[i] = neg[j];
			}
			else if(op == '-'){
				int i,j;
				cin>>i>>j;
				src[i] = src[j];
				neg[i] = !neg[j];
				if(src[i] == 0){
					src[i] = 1;
					neg[i] = 0;
				}
				else if(src[i] == 1){
					src[i] = 0;
					neg[i] = 0;
				}
				else if(src[i] == 2){
					src[i] = 2;
					neg[i] = 0;
				}
			}
		}
		for(int i = 1;i <= n;i++){
			int s = src[i];
			int ng = neg[i];
			if(s == 2){
				ukl.push_back(i);
			}
			else if(s == 0){
				unite(i, rtt);
				unite(i+n, rtf);
			}
			else if(s == 1){
				unite(i, rtf);
				unite(i+n, rtt);
			}
			else{
				int j = s - 2;
				if(ng == 0){
					unite(i, j);
					unite(i+n, j+n);
				}
				else{
					unite(i, j+n);
					unite(i+n, j);
				}
			}
		}
		for(auto x : ukl){
			uk[find(x)] = 1;
			uk[find(x + n)] = 1;
		}
		for(int i = 1;i <= n;i++){
			if(find(i) == find(i + n)){
				uk[find(i)] = 1;
			}
		}
		int ans = 0;
		for(int i = 1;i <= n;i++){
			if(uk[find(i)] == 1 || uk[find(i + n)] == 1){
				ans++;
			}
		}
		cout<<ans<<"\n";
	}
}

signed main(){
	process();
	return 0;
}
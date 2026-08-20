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
#define f first
#define s second
#define pr pair<int, int>
// #define int long long

#define num (500000 + 5)
#define lg2n (lg(num) + 5)

using namespace std;

int n, m;
int dp[num][lg2n];
vector<vector<int>> tr;
vector<int> dep;

void dfs(int u, int fa){
	dp[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for_1(lg2n - 1){
		dp[u][i] = dp[dp[u][i - 1]][i - 1];
	}
	for(auto v : tr[u]){
		if(v != fa){
			dfs(v, u);
		}
	}
}
int lca(int u, int v){
	if(dep[u] < dep[v]){
		swap(u, v);
	}
	int step = dep[u] - dep[v];
	for_0(lg2n){
		if(step & (1 << i)){
			u = dp[u][i];
		}
	}
	if(u == v){
		return u;
	}
	for(int j = lg2n - 1; j >= 0; j--){
		if(dp[u][j] != dp[v][j]){
			u = dp[u][j];
			v = dp[v][j];
		}
	}
	return dp[u][0];
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	tr.resize(n + 5);
	dep.resize(n + 5);
	for_0(n - 1){
		int a, b;
		cin>>a>>b;
		tr[a].push_back(b);
		tr[b].push_back(a);
	}
	dep[0] = -1;
	dfs(1, 0);
	for_0(m){
		int x, y, z;
		cin>>x>>y>>z;
		int xy = lca(x, y), xz = lca(x, z), yz = lca(y, z);
		int p;
		if(dep[xy] >= dep[xz] && dep[xy] >= dep[yz]){
			p = xy;
		}
		else if(dep[xz] >= dep[xy] && dep[xz] >= dep[yz]){
			p = xz;
		} 
		else{
			p = yz;
		}
		int c = dep[x] + dep[y] + dep[z] - dep[xy] - dep[xz] - dep[yz];

		cout<<p<<" "<<c<<"\n";
	}

	return 0;
}

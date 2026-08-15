#include<bits/stdc++.h>

using namespace std;

struct edge{
	int u, v, w;
};

vector<edge> edges;
vector<int> fa;
int n, m;

int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void unite(int x, int y){
	int rootx = find(x);
	int rooty = find(y);
	if(rootx != rooty) fa[rootx] = rooty;
}
int kruskal() {
	sort(edges.begin(), edges.end(), [](edge a, edge b){ return a.w < b.w; });
	int res = 0, cnt = 0;
	for(auto e : edges){
		if(find(e.u) != find(e.v)){
			unite(e.u, e.v);
			res += e.w;
			cnt++;
		}
	}
	if(cnt == n - 1){
		return res;
	}
	else{
		return INT_MIN;
	}
}

int main(){
	cin>>n>>m;
	for(int i = 0;i < m;i++){
		int u, v, w;
		cin>>u>>v>>w;
		edges.push_back({u, v, w});
	}
	fa.resize(n + 5);
	for(int i = 1;i <= n;i++) fa[i] = i;
	int ans = kruskal();
	if(ans == INT_MIN) cout<<"orz\n";
	else cout<<ans<<"\n";

	return 0;
}
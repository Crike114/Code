#include<bits/stdc++.h>
#define inf (INT_MIN >> 1)

using namespace std;

int d, p, c, f, s;
vector<vector<pair<int, int>>> gra;
vector<int> dist, cnt;
vector<bool> vis;

bool spfa(){
	dist.assign(c + 5, inf);
	vis.assign(c + 5, 0);
	cnt.assign(c + 5, 0);
	queue<int> q;
	dist[s] = d;
	vis[s] = 1;
	q.push(s);
	cnt[s] = 1;
	while(!q.empty()){
		int u = q.front();
		vis[u] = 0;
		q.pop();
		for(auto x : gra[u]){
			if(dist[x.first] < dist[u] + x.second){
				dist[x.first] = dist[u] + x.second;
				if(vis[x.first] != 1){
					vis[x.first] = 1;
					q.push(x.first);
					cnt[x.first]++;
					if(cnt[x.first] > c){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int main(){
	cin>>d>>p>>c>>f>>s;
	gra.resize(c + 5);
	dist.resize(c + 5);
	dist.assign(c + 5, inf);
	vis.resize(c + 5);
    cnt.resize(c + 5);
	for(int i = 0;i < p;i++){
		int u, v;
		cin>>u>>v;
        gra[u].push_back({v, d});
	}
    for(int i = 0;i < f;i++){
        int u, v, w;
        cin>>u>>v>>w;
        gra[u].push_back({v, d - w});
    }

	if(spfa() == 1){
        cout<<-1;
    }
    else{
        int ans = INT_MIN;
        for(int i = 1;i <= c;i++){
            if(dist[i] > ans && dist[i] != inf){
                ans = dist[i];
            }
        }
        cout<<ans;
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int n, m, k, cnt;
vector<int> fa;
vector<int> ans;
stack<int> s;
vector<bool> dtd;
multimap<int, int> mp;

void init(){
    for(int i = 0;i < n;i++){
        fa[i] = i;
    }
}
int find(int u){
    if(fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}
void unite(int u, int v){
    int ru = find(u), rv = find(v);
    if(ru != rv){
        fa[ru] = rv;
        cnt--;
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin>>n>>m;
    fa.resize(n);
    dtd.resize(n);
    for(int i = 0;i < m;i++){
        int x, y;
        cin>>x>>y;
        mp.insert({x, y});
        mp.insert({y, x});
    }
    cin>>k;
    ans.resize(k + 1);
    vector<int> attack(k);
    for(int i = 0;i < k;i++){
        cin>>attack[i];
        s.push(attack[i]);
        dtd[attack[i]] = true;
    }

    init();

    cnt = n - k;

    for(auto it = mp.begin();it != mp.end();it++){
        int u = it->first, v = it->second;

        if(u < v && dtd[u] == 0 && dtd[v] == 0){
            if(find(u) != find(v)){
                unite(u, v);
            }
        }
    }

    ans[k] = cnt;

    for(int i = k - 1;i >= 0;i--){
        int p = attack[i];
        dtd[p] = false;
        cnt++;
        auto range = mp.equal_range(p);
        
        for(auto it = range.first;it != range.second;++it){
            int v = it->second;
            if(dtd[v] == 0){
                if(find(p) != find(v)){
                    unite(p, v);
                }
            }
        }
        ans[i] = cnt;
    }

    for(int i = 0;i <= k;i++){
        cout<<ans[i]<<"\n";
    }
}
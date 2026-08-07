#include<bits/stdc++.h>
using namespace std;

int n, k, cnt;
vector<int> parent;
vector<int> w;

int find(int x){
    if(parent[x] == x){
        return x;
    }
    int p = parent[x];
    int root = find(p);
    w[x] = (w[x] + w[p]) % 3;
    return parent[x] = root;
}
int unionset(int x, int y, int val){
    parent[x] = y;
    w[x] = val;
    return 0;
}
// bool check(int x, int y){

// }
int init(int n){
    for(int i = 1;i <= n;i++){
        parent[i] = i;
        w[i] = 0;
    }
    return 0;
}

int main(){
    cin>>n>>k;
    parent.resize(n + 1);
    w.resize(n + 1);
    init(n + 1);

    for(int i = 1;i <= k;i++){
        int z, a, b;
        cin>>z>>a>>b;
        if((a > n || b > n) || (z == 2 && a == b)){
            cnt++;
            continue;
        }
        int u = find(a), v = find(b);
        if(z == 1){
            if(u == v && w[a] != w[b]){
                cnt++;
                continue;
            }
            else if(u != v){
                unionset(u, v, (w[b] - w[a] + 3) % 3);
            }
        }
        else if(z == 2){
            if(u == v){
                if((w[a] - w[b] + 3) % 3 != 1){
                    cnt++;
                    continue;
                }
            }
            else{
                unionset(u, v, (w[b] - w[a] + 4) % 3);      
            }
        }
    }
    cout<<cnt<<"\n";
    return 0;
}
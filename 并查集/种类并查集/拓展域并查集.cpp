#include<bits/stdc++.h>
using namespace std;

struct prisoner{
    int p1, p2, c;
};
int n, m;
vector<int> parent;
vector<prisoner> c;

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}
int unionset(int x, int y){
    int xp = find(x);
    int yp = find(y);
    if(xp == yp) return 0;
    parent[xp] = yp;
    return 0;
}
bool check(int x, int y){
    if(find(x) == find(y)) return 1;
    return 0;
}
int init(int n){
    for(int i = 1;i <= 2 * n;i++){
        parent[i] = i;
    }
    return 0;
}

int main(){
    cin>>n>>m;
    parent.resize(2 * n + 1);
    c.resize(m);
    init(n);
    for(int i = 0;i < m;i++){
        int a, b, x;
        cin>>a>>b>>x;
        c[i] = {a, b, x};
    }
    sort(c.begin(), c.end(), [](prisoner x, prisoner y){ return x.c > y.c; });
    for(int i = 0;i < m;i++){
        int u = c[i].p1, v = c[i].p2;
        unionset(u, v + n);
        unionset(v, u + n);
        if(check(u, u + n) || check(v, v + n)){
            cout<<c[i].c;
            return 0;
        }
    }
    cout<<0;
    return 0;
}
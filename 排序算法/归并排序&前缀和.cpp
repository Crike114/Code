#include<bits/stdc++.h>
using namespace std;

long long n, ans;
vector<int> ab;
vector<int> tmp;

void mg(vector<int>::iterator a, vector<int>::iterator b, vector<int>::iterator c, vector<int>::iterator d, vector<int>::iterator tg){
    vector<int>::iterator it1 = a, it2 = c, ittmp = tg;
    while(it1 < b && it2 < d){
        if(*it1 <= *it2){
            *ittmp = *it1;
            ittmp++;
            it1++;
        }
        else{
            ans += (b - it1);
            *ittmp = *it2;
            ittmp++;
            it2++;
        }
    }
    while(it1 < b){
        *ittmp = *it1;
        ittmp++;
        it1++;
    }
    while(it2 < d){
        *ittmp = *it2;
        ittmp++;
        it2++;
    }
}

void mgst(vector<int>& a, int l, int r){
    if(r - l <= 1) return;
    int mid = (r + l) / 2;
    mgst(a, l, mid);
    mgst(a, mid, r);
    
    mg(a.begin() + l, a.begin() + mid, a.begin() + mid, a.begin() + r, tmp.begin() + l);
    for(int i = l;i < r;i++){
        a[i] = tmp[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin>>n;
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        ab.push_back(x);
    }
    
    tmp.resize(n);
    if(n > 0){
        mgst(ab, 0, ab.size());
    }
    for(auto x : ab) cout<<x<<' ';
    // cout<<ans<<endl;
    return 0;
}
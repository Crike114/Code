#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
int efg = 0;

int check(int i); 
int poptop(){
    swap(a[1], a[efg]);
    efg--;
    check(1);
    return 0;
}
int check(int i){
	if (i > efg || i * 2 > efg) return 0;
	int x;
	if(i * 2 + 1 <= efg){
        if (a[i * 2] >= a[i * 2 + 1])
            x = i * 2;
        else
            x = i * 2 + 1;
    }
    else{
        x = i * 2;
    }
    if(a[x] > a[i] && x <= efg){
        swap(a[i], a[x]);
        return check(x);
    }
    return 0;
}
int build(){
    for(int i = n / 2;i >= 1;i--){
        check(i);
    }
    return 0;
}

int main(){
    cin>>n;
    a.resize(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    efg = n;
    build();
    for(int i = 1;i <= n;i++){
        poptop();
    }

    for(int i = 1;i <= n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
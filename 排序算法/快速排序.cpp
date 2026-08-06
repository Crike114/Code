#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int qkst(int l, int r){
    if(l >= r){
        return 0;
    }

    // int rnum;
    // do{
    //     int rnum = (rand() % (r - l + 1)) + l;
    // }
    // while(rnum != l);

    // swap(a[l], a[rnum]);
    int rnum = l + rand() % (r - l + 1);
    swap(a[l], a[rnum]);

    int i = l + 1, j = r;
    int pivot = a[l];

    while(i <= j){
        while(i <= r && a[i] < pivot) i++;
        while(j >= l && a[j] > pivot) j--;
        if(i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    swap(a[l], a[j]); 
    qkst(l, j - 1);
    qkst(j + 1, r);
    return 0;
}

int main(){
    // srand(time(0));
    cin>>n;
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        a.push_back(x);
    }
    qkst(0, n - 1);
    for(auto x : a) cout<<x<<" ";
    return 0;
}

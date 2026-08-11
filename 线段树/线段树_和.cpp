#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m, L, R;
vector<int> a, s, tag;

void pushup(int rt){
    s[rt] = s[rt << 1] + s[rt << 1 | 1];
}
void pushdown(int l, int r, int rt){
    if(tag[rt] != 0){
		int mid = (l + r) >> 1;
		tag[rt << 1] += tag[rt];
		s[rt << 1] += tag[rt] * (mid - l + 1);
		tag[rt << 1 | 1] += tag[rt];
		s[rt << 1 | 1] += tag[rt] * (r - mid);
		tag[rt] = 0;
	}
}
void build(int l, int r, int rt){
    if(l == r){
        s[rt] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushup(rt);
}
void update(int x, int y, int l, int r, int c, int rt){
	if(l > y || r < x){
		return; 
	}
    if(l <= x && y <= r){
        s[rt] += c * (y - x + 1);
        tag[rt] += c;
        return;
    }
    pushdown(x, y, rt);
    int mid = (x + y) >> 1;
    if(l <= mid){
        update(x, mid, l, r, c, rt << 1);
    }
    if(r > mid){
        update(mid + 1, y, l, r, c, rt << 1 | 1);
    }
    pushup(rt);
}
int quary(int x, int y, int l, int r, int rt){
	if(x > r || y < l){
		return 0;
	}
    int sum = 0;
    if(x <= l && r <= y){
        return s[rt];
    }
    int mid = (l + r) >> 1;
    pushdown(l, r, rt);
    if(x <= mid){
        sum += quary(x, y, l, mid, rt << 1);
    }
    if(y > mid){
        sum += quary(x, y, mid + 1, r, rt << 1 | 1);
    }
    return sum;
}

void init(){
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0)->sync_with_stdio(0);
}
void input(){
    cin>>n>>m;
    L = 1, R = n;
    a.resize(n + 5);
    s.resize(4 * n + 5);
	tag.resize(4 * n + 5);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
}
void output(){
    int op, x, y, k;
    for(int i = 1;i <= m;i++){
        cin>>op>>x>>y;
        if(op == 1){
            cin>>k;
            update(L, R, x, y, k, 1);
        }
        else if(op == 2){
            cout<<quary(x, y, 1, n, 1)<<"\n";
        }
    }
}

signed main(){
    init();
    input();
    build(1, n, 1);
    output();

    return 0;
}
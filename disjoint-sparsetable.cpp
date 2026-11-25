#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXLOG = 20;

int n, q;
int arr[MAXN];
int table[MAXLOG][MAXN];

int operacion(int a, int b){
    if(a > b) return a;
    return b;
}

void build_dst(){
    for(int i = 0; i< n; i++){
        table[0][i] = arr[i];
    }
    for(int level = 1; (1 << level) <= n; level++){
        int block_size = (1 << level);
        int half = block_size / 2;
        for(int center = half; center < n; center += block_size){
            table[level][center - 1] = arr[center - 1];
            for(int i = center - 2; i>= center - half && i>= 0; i--){
                table[level][i] = operacion(arr[i], table[level][i + 1]);
            }
            table[level][center] = arr[center];
            int limit = min(n, center + half);
            for(int i = center + 1; i< limit; i++){
                table[level][i] = operacion(table[level][i - 1], arr[i]);
            }
        }
    }
}

int query(int l, int r){
    if(l == r) return table[0][l];
    int level = 31 - __builtin_clz(l ^ r);
    return operacion(table[level][l], table[level][r]);
}

void solve(){
    cin>>n>>q;
    for(int i = 0; i< n; i++){
        cin>>arr[i];
    }
    build_dst();
    for(int i = 0; i< q; i++){
        int l, r;
        cin>>l>>r;
        int ans = query(l, r);
        cout<<ans<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

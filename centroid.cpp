#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int sz[MAXN];
bool removed[MAXN];
int centroid_parent[MAXN];
int n, q;

void calc_sizes(int u, int p){
    sz[u] = 1;
    for(int v : adj[u]){
        if(v != p && !removed[v]){
            calc_sizes(v, u);
            sz[u] += sz[v];
        }
    }
}

int find_centroid(int u, int p, int total_tree_size){
    for(int v : adj[u]){
        if(v != p && !removed[v] && sz[v] > total_tree_size / 2){
            return find_centroid(v, u, total_tree_size);
        }
    }
    return u;
}

int decompose(int u){
    calc_sizes(u, -1);
    int c = find_centroid(u, -1, sz[u]);
    removed[c] = true;
    for(int v : adj[c]){
        if(!removed[v]){
            int next_c = decompose(v);
            centroid_parent[next_c] = c;
        }
    }
    return c;
}

void solve(){
    cin>>n;
    for(int i = 0; i< n - 1; i++){
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(removed, false, sizeof(removed));
    memset(centroid_parent, -1, sizeof(centroid_parent));
    decompose(1);
    for(int i = 1; i<= n; i++){
        cout<<"Nodo "<<i<<": Padre Centroide = "<<centroid_parent[i]<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

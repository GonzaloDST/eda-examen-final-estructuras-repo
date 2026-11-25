#include <bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
    Node(int v){
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

Node* build(int l, int r){
    if(l > r) return nullptr;
    int mid = (l + r) / 2;
    Node* root = new Node(mid);
    root->left = build(l, mid - 1);
    root->right = build(mid + 1, r);
    return root;
}

void get_paths(Node* root, int target, vector<pair<int, char>>& camino){
    Node* curr = root;
    while(curr){
        if(target == curr->val) break;
        if(target < curr->val){
            camino.push_back({curr->val, 'L'});
            curr = curr->left;
        }
        else{
            camino.push_back({curr->val, 'R'});
            curr = curr->right;
        }
    }
}

void solve(){
    int n, m;
    cin>>n>>m;
    
    vector<int> queries(m);
    for(int i = 0; i< m; i++){
        cin>>queries[i];
    }
    Node* refTree = build(1, n);
    map<int, vector<char>> history;
    for(int i = 0; i< m; i++){
        vector<pair<int, char>> camino;
        get_paths(refTree, queries[i], camino);
        for(int j = 0; j< (int)camino.size(); j++){
            history[camino[j].first].push_back(camino[j].second);
        }
    }
    int total_wb = 0;
    for(int i = 1; i<= n; i++){
        vector<char>& seq = history[i];
        int changes = 0;
        for(int j = 1; j< (int)seq.size(); j++){
            if(seq[j] != seq[j - 1]){
                changes++;
            }
        }
        total_wb += changes;
    }
    cout<<total_wb<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

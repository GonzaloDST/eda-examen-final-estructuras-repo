#include <bits/stdc++.h>
using namespace std;

const int BLOCK_SIZE = 4;

struct BTreeNode{
    bool leaf;
    vector<int> keys;
    vector<BTreeNode*> children;
    BTreeNode(bool is_leaf){
        leaf = is_leaf;
    }
};

struct BTree{
    BTreeNode* root;
    int io_count;
    BTree(){
        root = new BTreeNode(true);
        io_count = 0;
    }

    void split_child(BTreeNode* parent, int idx, BTreeNode* full_node){
        io_count += 2;
        BTreeNode* sibling = new BTreeNode(full_node->leaf);
        int mid = BLOCK_SIZE / 2;
        int up_key = full_node->keys[mid];
        for(int i = mid + 1; i< BLOCK_SIZE; i++){
            sibling->keys.push_back(full_node->keys[i]);
        }
        if(!full_node->leaf){
            for(int i = mid + 1; i<= BLOCK_SIZE; i++){
                sibling->children.push_back(full_node->children[i]);
            }
        }
        full_node->keys.resize(mid);
        if(!full_node->leaf){
            full_node->children.resize(mid + 1);
        }
        parent->children.insert(parent->children.begin() + idx + 1, sibling);
        parent->keys.insert(parent->keys.begin() + idx, up_key);
        io_count++;
    }

    void insert_non_full(BTreeNode* node, int key){
        io_count++;
        int pos = node->keys.size() - 1;
        if(node->leaf){
            node->keys.push_back(0);
            while(pos >= 0 && node->keys[pos] > key){
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        }
        else{
            while(pos >= 0 && node->keys[pos] > key){
                pos--;
            }
            pos++;
            if((int)node->children[pos]->keys.size() == BLOCK_SIZE){
                split_child(node, pos, node->children[pos]);
                if(node->keys[pos] < key){
                    pos++;
                }
            }
            insert_non_full(node->children[pos], key);
        }
    }

    void insert(int key){
        BTreeNode* r = root;
        if((int)r->keys.size() == BLOCK_SIZE){
            BTreeNode* s = new BTreeNode(false);
            root = s;
            s->children.push_back(r);
            split_child(s, 0, r);
            insert_non_full(s, key);
        }
        else{
            insert_non_full(r, key);
        }
    }

    bool search(BTreeNode* node, int key){
        if(!node) return false;
        io_count++;
        int idx = 0;
        while(idx < (int)node->keys.size() && key > node->keys[idx]){
            idx++;
        }
        if(idx < (int)node->keys.size() && key == node->keys[idx]){
            return true;
        }
        if(node->leaf){
            return false;
        }
        return search(node->children[idx], key);
    }
};

void solve(){
    int n, q;
    cin>>n>>q;
    BTree disk_tree;
    for(int i = 0; i< n; i++){
        int val;
        cin>>val;
        disk_tree.insert(val);
    }
    for(int i = 0; i< q; i++){
        int query_val;
        cin>>query_val;
        int prev_io = disk_tree.io_count;
        bool found = disk_tree.search(disk_tree.root, query_val);
        int current_io = disk_tree.io_count - prev_io;
        if(found){
            cout<<"FOUND "<<current_io<<"\n";
        }
        else{
            cout<<"NOT_FOUND "<<current_io<<"\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int W = 16;

struct XFastNode{
    int val;
    XFastNode* left;
    XFastNode* right;
    XFastNode* desc_left;
    XFastNode* desc_right;
    XFastNode* prev;
    XFastNode* next;
    XFastNode(int v){
        val = v;
        left = nullptr;
        right = nullptr;
        desc_left = nullptr;
        desc_right = nullptr;
        prev = nullptr;
        next = nullptr;
    }
};

struct XFastTrie{
    XFastNode* root;
    unordered_map<int, XFastNode*> levels[W + 1];
    XFastNode* head;

    XFastTrie(){
        root = new XFastNode(-1);
        levels[0][0] = root;
        head = nullptr;
    }

    void insert(int x){
        XFastNode* curr = root;
        vector<XFastNode*> path_nodes;
        path_nodes.push_back(curr);
        for(int i = W - 1; i>= 0; i--){
            int bit = (x >> i) & 1;
            int prefix = (x >> i);
            int nivel = W - i;
            if(bit == 0){
                if(!curr->left){
                    curr->left = new XFastNode(-1);
                    levels[nivel][prefix] = curr->left;
                }
                curr = curr->left;
            }
            else{
                if(!curr->right){
                    curr->right = new XFastNode(-1);
                    levels[nivel][prefix] = curr->right;
                }
                curr = curr->right;
            }
            path_nodes.push_back(curr);
        }
        curr->val = x;
        if(!head){
            head = curr;
        }
        else{
            XFastNode* temp = head;
            XFastNode* prev_node = nullptr;
            while(temp && temp->val < x){
                prev_node = temp;
                temp = temp->next;
            }
            if(!prev_node){
                curr->next = head;
                head->prev = curr;
                head = curr;
            }
            else{
                curr->next = temp;
                curr->prev = prev_node;
                prev_node->next = curr;
                if(temp){
                    temp->prev = curr;
                }
            }
        }
        for(int i = 0; i< (int)path_nodes.size(); i++){
            XFastNode* n = path_nodes[i];
            if(!n->desc_left || x < n->desc_left->val){
                n->desc_left = curr;
            }
            if(!n->desc_right || x > n->desc_right->val){
                n->desc_right = curr;
            }
        }
    }

    int successor(int x){
        int low = 0, high = W, lcp_level = 0;
        XFastNode* ancestor = root;
        while(low <= high){
            int mid = (low + high) / 2;
            int pref = (x >> (W - mid));
            if(levels[mid].count(pref)){
                lcp_level = mid;
                ancestor = levels[mid][pref];
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        if(lcp_level == W) return x;
        int next_bit = (x >> (W - lcp_level - 1)) & 1;
        XFastNode* candidate = nullptr;
        if(next_bit == 0){
            candidate = ancestor->desc_right;
        }
        else{
            candidate = ancestor->desc_left;
        }
        if(!candidate) return -1;
        if(candidate->val >= x) return candidate->val;
        if(candidate->next) return candidate->next->val;
        return -1;
    }
};

void solve(){
    int n, q;
    cin>>n>>q;
    XFastTrie xfast;
    for(int i = 0; i< n; i++){
        int val;
        cin>>val;
        xfast.insert(val);
    }
    for(int i = 0; i< q; i++){
        int query_val;
        cin>>query_val;
        int ans = xfast.successor(query_val);
        cout<<ans<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

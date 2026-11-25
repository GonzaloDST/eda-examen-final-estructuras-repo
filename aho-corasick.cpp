#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode{
    int next_node[ALPHABET_SIZE];
    int link;
    int exit_link;
    vector<int> pattern_indices;

    TrieNode(){
        memset(next_node, -1, sizeof(next_node));
        link = -1;
        exit_link = -1;
    }
};

vector<TrieNode> trie;





void trie_insert(const string& s, int pattern_idx){
    int current =0;
    for(int i =0; i< (int)s.length(); i++){
        int c = s[i] - 'a';
        if(trie[current].next_node[c]==-1){

            trie[current].next_node[c] = trie.size();
            trie.push_back(TrieNode());
        }
        current = trie[current].next_node[c];
    }
    trie[current].pattern_indices.push_back(pattern_idx);
}

void build_aho_corasick(){
    queue<int> q;
    trie[0].link = 0;

    for(int c = 0; c< ALPHABET_SIZE; c++){
        if(trie[0].next_node[c] != -1){
            trie[trie[0].next_node[c]].link = 0;
            q.push(trie[0].next_node[c]);
        }
        else{
            trie[0].next_node[c] = 0;
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        int fallback = trie[u].link;
        if(!trie[fallback].pattern_indices.empty()){
            trie[u].exit_link = fallback;
        }
        else{
            trie[u].exit_link = trie[fallback].exit_link;
        }
        for(int c = 0; c< ALPHABET_SIZE; c++){
            if(trie[u].next_node[c] != -1){
                trie[trie[u].next_node[c]].link = trie[fallback].next_node[c];
                q.push(trie[u].next_node[c]);
            }
            else{
                trie[u].next_node[c] = trie[fallback].next_node[c];
            }
        }
    }
}

void solve(){
    int num_patterns;
    cin>>num_patterns;
    trie.clear();
    trie.push_back(TrieNode());
    vector<string> patterns(num_patterns);
    for(int i = 0; i< num_patterns; i++){
        cin>>patterns[i];
        trie_insert(patterns[i], i);
    }
    build_aho_corasick();
    string texto;
    cin>>texto;
    int state = 0;
    for(int i = 0; i< (int)texto.length(); i++){
        int c = texto[i] - 'a';
        state = trie[state].next_node[c];
        int check_state = state;
        while(check_state > 0){
            for(int idx : trie[check_state].pattern_indices){
                cout<<"Match pattern "<<idx<<" at position "<<i<<"\n";
            }
            check_state = trie[check_state].exit_link;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}

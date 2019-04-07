#include <iostream>
#include <deque>
#include "trie.h"

void Trie::add_string( std::string str){
    TrieNode* current = &root;
    for (auto pchar = str.cbegin(); pchar != str.cend(); pchar++ ) {
        char c = *pchar;
        int index = static_cast<int>(c);

        //std::cout << "New char " << c << std::endl;

        if ( current->char_index[index] == -1 ) {
            //std::cout << "Making new node for " << c << std::endl;
            // add new node
            current->child_nodes.emplace_back(c);
            //std::cout << "Updating index vector " << index << " points to loc " << current->child_nodes.size()-1 << std::endl;
            current->char_index[index] = current->child_nodes.size()-1;
        }
        //std::cout << "Updating node for " << c << std::endl;
        int child_index = current->char_index[index];
        current = &(current->child_nodes[child_index]);
    }

}

void Trie::build_trie (std::vector<std::string> entries) {
    for (auto pstr = entries.cbegin(); pstr != entries.cend(); pstr++) {
        const std::string s = *pstr;
        //std::cout << "Adding string: " << s << std::endl; 
        add_string(s);
        //std::cout << "Completing string: " << s << std::endl;
    }
}

std::vector<std::string> Trie::get_completions(std::string s){
    TrieNode *current = &root;
    for (auto pstr = s.cbegin(); pstr != s.cend(); pstr++) {
        char c = *pstr;
        int index = static_cast<int>(c);
        int node_index = current->char_index[index];
        if (node_index == -1) {
            return std::vector<std::string>();
        }
        current = &(current->child_nodes[node_index]);
    }

    // now search through subtree with current as root
    std::vector<std::string> completions;
    scan_nodes(*current, completions, s);
    return completions;
}

void Trie::scan_nodes(const TrieNode& node, std::vector<std::string>& completions, std::string complete_str) {

    // base case: assumes that completions end at leaf nodes of trie
    if (node.child_nodes.empty()){
        completions.push_back(complete_str);
        return;
    }
    
    for (auto pchild = node.child_nodes.cbegin(); pchild != node.child_nodes.cend(); pchild++){
        std::string s(complete_str);
        char next_char = (*pchild).get_char(); 
        s+= next_char;
        scan_nodes( (*pchild), completions, s);
    }
}

void Trie::print_trie(){
    std::deque<TrieNode*> dfs_stack;
    dfs_stack.push_back(&root);

    while(!dfs_stack.empty()) {
        TrieNode* current = dfs_stack.back();
        dfs_stack.pop_back();
        for (auto i = current->child_nodes.begin(); i != current->child_nodes.end(); i++){
            dfs_stack.push_back(&(*i));
        }
        current->print_node();
    }
}
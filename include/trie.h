#include <iostream>
#include <string>
#include <vector>

void run_trie_test();
std::vector<std::string> readSWDialog(const char* filename);

class TrieNode{
public: 
    TrieNode() : c('*'), child_nodes(), char_index(128,-1) { }
    TrieNode(char new_c) : c(new_c), child_nodes(), char_index(128,-1) { }
    char get_char() const {return c;}
    void print_node() {
        std::cout << "Node " << get_char() << " has " << child_nodes.size() << " children" << std::endl;
        for (auto n : child_nodes){
            std::cout << "\thas node " << n.get_char() << std::endl;   
        }
    };

private:
    char c;

public:
    std::vector<TrieNode> child_nodes;
    std::vector<int> char_index;
};

class Trie{
public:
    Trie() {};
    void build_trie ( std::vector<std::string> );
    std::vector<std::string> get_completions ( std::string );
    void print_trie();
private:
    void add_string ( std::string s ); 
    void scan_nodes(const TrieNode&, std::vector<std::string>&, std::string);
    TrieNode root;
};
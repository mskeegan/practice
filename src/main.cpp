#include <iostream>
#include <vector>

#include "trie.h"
#include "algo.h"
#include "graph_algorithms.h"

using namespace std;


vector<bool> run_test{false,false,false,true,false,false};

int main() {
    if (run_test[0]){
        run_trie_test();
    } else if (run_test[1]) {
        lsubseq_test(); // find longest subsequence  
    } else if (run_test[2]) {
        palindrome_test(); 
    } else if (run_test[3]) {
        test_sorts();
    } else if (run_test[4]) {
        test_find_connected_components();
    } else if (run_test[5]) {
        test_subset_searches();
        test_permutation_searches();
    }
}
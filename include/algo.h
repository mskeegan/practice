#include <cstdlib>
#include <vector>

using namespace std;

// Longest Subsequence Tests
void lsubseq_test();
void palindrome_test();

// Sort Algorithms
template <typename T>
void heap_sort(T*,size_t);
void test_sorts();

// Combinatorial Search Functions
int find_all_subsets(int n, vector<vector<int>>& solutions);
int find_all_permutations(int n, vector<vector<int>>& solutions);
bool test_subset_searches();
bool test_permutation_searches();

#include "algo.h"

int compute_next_subset_candidates(int* c) {
    c[0] = 0;
    c[1] = 1;
    return 2;
}

int backtrack_subset_dfs(int *x, int k, vector<vector<int>>& solutions, int n) {
    int num_solutions = 0;
    if (k==n){
        vector<int> s(x,x+k);
        solutions.push_back(s);
        num_solutions++;
        return num_solutions;
    }

    int* c = new int[2];
    int num_c = compute_next_subset_candidates(c);
    for (int j = 0; j < num_c; j++){
        x[k] = c[j];
        num_solutions += backtrack_subset_dfs(x,k+1,solutions,n);
    }
    delete [] c;
    return num_solutions;
}

int find_all_subsets(int n, vector<vector<int>>& solutions) {
    int* x = new int[n];
    int total_solutions = backtrack_subset_dfs(x,0,solutions,n);
    delete [] x;
    return total_solutions;
}

int compute_next_permutation_candidates(int* x,int k, int n, int* c) {
    int new_candidates = 0;
    for (int i = 0; i < n; i++){
        bool included = false;
        for (int j = 0; j < k; j++) {
            if (x[j] == i ){
                included = true;
            }
        }
        if (!included) {
            c[new_candidates++] = i;
        }
    }
    return new_candidates;
}

int backtrack_permutation_dfs(int *x, int k, vector<vector<int>>& solutions, int n) {
    int num_solutions = 0;
    if (k==n){
        vector<int> s(x,x+k);
        solutions.push_back(s);
        num_solutions++;
        return num_solutions;
    }

    int* c = new int[2];
    int num_c = compute_next_permutation_candidates(x,k,n,c);
    for (int j = 0; j < num_c; j++){
        x[k] = c[j];
        num_solutions += backtrack_permutation_dfs(x,k+1,solutions,n);
    }
    delete [] c;
    return num_solutions;
}

int find_all_permutations(int n, vector<vector<int>>& solutions) {
    int* x = new int[n];
    int total_solutions = backtrack_permutation_dfs(x,0,solutions,n);
    delete [] x;
    return total_solutions;
}
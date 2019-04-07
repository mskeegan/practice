#include <cmath>
#include <iostream>
#include <vector>

#include "algo.h"

int factorial(int n) {
    if (n < 1) return 0; //case not dealt with correctly
    int answer = 1;
    for (int i = 1; i <= n; i++){
        answer *= i;
    }
    return answer;
}

bool test_subset_searches(){

    int n = 5;
    vector<vector<int>> solutions;
    int num_subsets = find_all_subsets(n, solutions);
    cout << "Number of Subsets: " << num_subsets << endl;
    for (auto subset : solutions) {
        int i = 0;
        for (int elem : subset ) {
            i++;
            if (elem) {
               cout << i << " ";
            }
        }
        cout << endl;
    }
    bool passed = true;
    if (num_subsets != pow(2,n)) {
        passed = false;
        cout << "Subset search failed" << endl;
    }
    return passed;
}

bool test_permutation_searches(){

    int n = 5;
    vector<vector<int>> solutions;
    int num_subsets = find_all_permutations(n, solutions);
    cout << "Number of Subsets: " << num_subsets << endl;
    for (auto p : solutions) {
        for (int elem : p ) {
            cout << elem << " ";
        }
        cout << endl;
    }
    bool passed = true;
    if (num_subsets != factorial(n)) {
        passed = false;
        cout << "Permutation search failed" << endl;
    }
    return passed;
}
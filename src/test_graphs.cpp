#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "graph_algorithms.h"

using namespace std;

bool test_find_connected_components(){

    connected_components c;
    int nVert(6);
    int nEdges(3);
    int edges[3][2] = {{1,4},{4,5},{3,2}};
    //int** edge_ptr;
    //edge_ptr = edges;
    c.find_all_connected_components(nVert,edges,nEdges);

    int true_components[6] = {1,2,2,1,1,3};

    cout << "Number of components: " << c.num_components << endl;
    cout << "Components: " << endl;
    bool agree = true;
    for (int i = 1; i <= 6; i++) {
        if (true_components[i-1] != c.component[i])
            agree = false;
        cout << c.component[i] << "  ";
    }
    cout << endl;
    if (!agree)
        cout << "Connected components test failed!" << endl;
    return agree;
}

bool test_minimum_spanning_tree_prim_c(){

    int nVec = 10;
    vector<int*> edge_vec;
    srand(time(0));
    for (int i = 0; i < nVec; i++){
        for (int j = i+1; j < nVec ; j++){
            if (rand() % 4 == 0) {
                int e[3] = {i,j,rand() % nVec + 1};
                edge_vec.emplace_back(e);
            }
        }
    }

    int nEdge = edge_vec.size();
    int** edges = &(edge_vec[0]);
    int* mst_edges; 
    int total_weight = mst_prim_c(nVec,edges,nEdge,&mst_edges);

    return false;
}
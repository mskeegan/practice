#include "graph_algorithms.h"

int connected_components::find_all_connected_components(int nVertices, int edges[][2], int nEdges){
    if (nVertices >= MAX_V){
        //Error case: print something
        return 0;
    }

    for (int i = 1; i <= nVertices; i++) {
        included[i] = false;
        component[i] = false;
    }

    for (int i = 1; i <= nVertices; i++){
        if (!included[i]){
            num_components++;
            int numVertConnected = find_component_dfs(i,edges,nEdges);
            component_sizes[num_components] = numVertConnected;
        }
    }
    return num_components;
}

int connected_components::find_component_dfs(int v, int edges[][2], int nEdges) {

    included[v] = true;
    component[v] = num_components;
    int nChildren = 0;
    for (int j = 0; j < nEdges; j++){
        if (edges[j][0] == v){
            int w = edges[j][1];
            if (!included[w]){
                nChildren += find_component_dfs(w,edges,nEdges);
            }
        }
        if (edges[j][1] == v){
            int w = edges[j][0];
            if (!included[w]){
                nChildren += find_component_dfs(w,edges,nEdges);
            }
        }
    }
    nChildren++;
    return nChildren;
}
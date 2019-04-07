
/**
 * Connected Components 
 **/
class connected_components{
    const static int MAX_V = 50;
public:
    int num_components = 0;
    bool included[MAX_V+1];
    int component[MAX_V+1];
    int component_sizes[MAX_V+1];

    int find_all_connected_components(int nVertices, int edges[][2], int nEdges);
private:
    int find_component_dfs(int v, int edges[][2], int nEdges);
};


// Minimum Spanning Tree C-functions
int mst_prim_c(int numVertices, int** edges, int numEdges, int **mst_edges);


// test functions
bool test_find_connected_components();
bool test_find_minimum_spanning_tree_prim_c();


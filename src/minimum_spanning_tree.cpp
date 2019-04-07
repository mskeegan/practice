#include <climits>
#include <iostream>
#include <vector>

#include "data_structs.h"
#include "graph_algorithms.h"

class Weighted_Edge{
public:
    Weighted_Edge() : id(0), weight(0), nodes {0,0} {}
    Weighted_Edge(int _id, int _weight, int _nodes[2]) : id(_id), weight(_weight) { nodes[0] = _nodes[0]; nodes[1] = _nodes[1]; }
    int id;
    int nodes[2];
    int weight;
};

bool operator<(const Weighted_Edge& lhs, const Weighted_Edge& rhs) {
    return lhs.weight < rhs.weight;
}

bool operator<=(const Weighted_Edge& lhs, const Weighted_Edge& rhs) {
    return !(lhs.weight > rhs.weight);
}

bool operator>(const Weighted_Edge& lhs, const Weighted_Edge& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Weighted_Edge& lhs, const Weighted_Edge& rhs) {
    return !(lhs < rhs);
}

class Node{
public:
    Node() : id(-1) {};
    Node(int _id) : id(_id) {};
    int id;
    vector<Weighted_Edge*> edges;
};

class Weighted_Graph{
public:
    vector<Node> node_set;
    vector<Weighted_Edge> edge_set;
    Weighted_Graph(int numVertices,int edges[][3],int numEdges) { make_graph(numVertices,edges,numEdges); }
    void make_graph(int numVertices,int edges[][3],int numEdges); 
};

void Weighted_Graph::make_graph(int numVertices,int edges[][3],int numEdges) {
    node_set.reserve(numVertices);
    edge_set.reserve(numEdges);
    for (int j = 0; j < numEdges; j++) {
        edge_set.emplace_back(j,edges[j][2], edges[j]);
    }
    for (int i = 0; i < numVertices; i++){
        node_set.emplace_back(i);
    }
    for (int j = 0; j < numEdges; j++){
        if (edge_set[j].nodes[0] == j || edge_set[j].nodes[1] == j) {
            node_set[j].edges.push_back(&(edge_set[j]));
        }
    }
}

int is_adjacent(int v, int* e) {
    if (e[0] == v || e[1] == v) return 1;
    return 0;
}

int get_neighbour(int v, int* e) {
    if (e[0] == v) return e[1];
    if (e[1] == v) return e[0];
    return -1;
}

bool mst_prim(int numVertices, int edges[][3], int numEdges, vector<int>& mst_edges) {

    Weighted_Graph g(numVertices,edges,numEdges);

    int* included = new int[numVertices];
    int included_count = 0;

    for (int i = 0; i < numVertices; i++) {
        included[i] = 0;
    }
    Heap<Weighted_Edge> edge_heap;

    included[0] = 1;
    included_count++;
    int v = 0;
    for (auto e : g.node_set[v].edges) {
        int w = get_neighbour(g.node_set[v].id,e->nodes);
        if (!included[w]) {
            edge_heap.insert(*e);
        }
    }

    while (included_count < numVertices) {
        if (edge_heap.is_empty()) {
            //error case
            cerr << "Graph is not fully connected. Exiting." << endl;
            return 0;
        }

        auto selected = edge_heap.get_top();
        mst_edges.push_back(selected.id);
        v = get_neighbour(v,selected.nodes);
        if (!included[v]) {
            included[v] = 1;
            for (auto e : g.node_set[v].edges) {
                int w = get_neighbour(g.node_set[v].id,e->nodes);
                if (!included[w]) {
                    edge_heap.insert(*e);
                }
            }
        }
    }

    delete []  included;
    return 1;
}

const int MAXV = 10000;

class cedgenode {
public:
    int id;
    int w;
    int weight;
    cedgenode* next = nullptr;
};

class cgraph {
public:
    cgraph(int numVertices, int** edges, int numEdges);
    ~cgraph();
    int* get_mst_edges(int* parents);
    int nvertices;
    int nedges;
    cedgenode *edgenodes[MAXV];
};

cgraph::cgraph(int numVertices, int** Edges, int numEdges) {

    for (int i = 0; i < MAXV; i++)
        edgenodes[i] = nullptr;

    nvertices = numVertices;
    nedges = numEdges;

    for (int i = 0; i < numEdges; i++) {
        int v1 = Edges[i][0];
        int v2 = Edges[i][1];

        cedgenode* edge1 = new cedgenode;
        edge1->weight = Edges[i][2];
        edge1->w = v2;
        edge1->next = edgenodes[v1];
        edge1->id = i;
        edgenodes[v1] = edge1;

        cedgenode* edge2 = new cedgenode;
        edge2->weight = Edges[i][2];
        edge2->w = v1;
        edge2->next = edgenodes[v2];
        edge2->id = i;
        edgenodes[v2] = edge2;
    }
}   

int* cgraph::get_mst_edges(int* parents) {
    int *mst_edges = new int[nvertices-1];
    int edge_count = 0;
    for(int v = 0; v < nvertices-1; v++) {
        int w = parents[v];
        cedgenode* e = edgenodes[v];
        while (e) {
            if (e->w == w) {
                mst_edges[edge_count++] = e->id;
                break;
            }
            e = e->next;
        }
    }
    return mst_edges;
}

cgraph::~cgraph() {
    for (int i = 0; i < MAXV; i++) {
        while (!edgenodes[i]) {
            cedgenode* c = edgenodes[i];
            edgenodes[i] = c->next;
            delete c;
        }
    }
}

int mst_prim_c(int numVertices, int** edges, int numEdges, int **mst_edges) {

    cgraph* g = new cgraph(numVertices,edges,numEdges);

    int* included = new int[g->nvertices];
    int* parent = new int[g->nvertices];
    int* distance = new int[g->nvertices];
    int total_weight = 0;

    for (int i = 0; i < g->nvertices; i++){
        included[i] = 0;
        parent[i] = -1;
        distance[i] = INT_MAX;

    }

    int v = 0;
    distance[v] = 0;

    while (!included[v]) {
        included[v] = 1;
        cedgenode* e = g->edgenodes[v]; 
        while (e) {
            int w = e->w;
            if (!included[w] && distance[w] > e->weight){
                distance[w] = e->weight;
            }
            e = e->next;
        }

        int min_current_distance = INT_MAX;
        int min_current_node = -1;
        for (int w = 0; w < g->nvertices ; w++){
            if (!included[w] && distance[w] < min_current_distance) {
                min_current_distance = distance[w];
            }
        }
        if (min_current_node != -1){
            total_weight += min_current_distance;
            parent[min_current_node] = v;
            v = min_current_node;
        }
    }

    *mst_edges = g->get_mst_edges(parent);

    delete [] included;
    delete [] distance;
    delete [] parent;
    delete g;
    return total_weight;
}
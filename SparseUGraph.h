#ifndef SparseUGraph_H
#define SparseUGraph_H

#include "UndirectedGraph.h"

class SparseUGraph: public UndirectedGraph
{
private:
    vector<vector<size_t>> v; //graph

    bool check(size_t i, size_t j);
    static size_t _count_triangles(SparseUGraph *g, size_t id=0, size_t skip=1);    
public:
    SparseUGraph(string filename);
    void print_graph(bool to_file=false);
    void print_row(size_t n_row);

    pair<size_t,size_t> count_triangles();
    pair<size_t,size_t> count_triangles_multi(size_t n_threads);
};

#endif
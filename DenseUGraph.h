#ifndef DenseUGraph_H
#define DenseUGraph_H

#include "UndirectedGraph.h"

class DenseUGraph: public UndirectedGraph
{
private:
    size_t size; //actual size
    vector<vector<bool>> triangular_matrix; //graph

    bool inline check(size_t i, size_t j);
    static size_t _count_triangles(DenseUGraph *g, size_t id=0, size_t skip=1);    
public:
    DenseUGraph(string filename);
    void print_graph(bool to_file=false);
    void print_row(size_t n_row);

    pair<size_t,size_t> count_triangles();
    pair<size_t,size_t> count_triangles_multi(size_t n_threads);
};

#endif
#ifndef MatrixUGraph_H
#define MatrixUGraph_H

#include "UndirectedGraph.h"

class MatrixUGraph: public UndirectedGraph
{
private:
    std::vector<std::vector<size_t>> matrix; //graph

    unsigned long long construction_time;

    void _create_matrix();

    static void _matrix_molt(std::vector<std::vector<size_t>> &a,
                                    std::vector<std::vector<size_t>> &b,
                                    std::vector<std::vector<size_t>> &mult,
                                    size_t n_nodes,
                                    size_t id=0, size_t skip=1);    
public:
    MatrixUGraph(std::string filename);
    MatrixUGraph(UndirectedGraph ug);

    void print_graph(bool to_file=false);
    void print_row(size_t n_row);

    unsigned long long get_construction_time();

    std::pair<unsigned long long,unsigned long long> count_triangles();
    std::pair<unsigned long long,unsigned long long> count_triangles_multi(size_t n_threads);
};

#endif
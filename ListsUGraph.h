#ifndef ListsUGraph_H
#define ListsUGraph_H

#include "UndirectedGraph.h"

class ListsUGraph: public UndirectedGraph
{
private:
    
    //List of adjusted nodes
    std::vector<std::pair<std::vector<size_t>,bool>> lists; //graph

    //time spent constructing List of adjusted nodes
    size_t construction_time;

    //load edges data structure from file
    void _load_edges(std::string dirname);

    //given a ListsUGraph object, count the number of triangles the graph,
    //other two parameters are for multithread execution
    static size_t _count_triangles(ListsUGraph *g, size_t id=0, size_t skip=1);   

public:
    ListsUGraph(std::string dirname);

    //print 'lists' data structure
    void print_graph(bool to_file=false);

    //print a specific list of 'lists' data structure
    void print_row(size_t n_row);

    //construction time getter
    size_t get_construction_time();

    //count triangle of this object (single thread)
    std::pair<size_t,size_t> count_triangles();

    //count triangle of this object (multi thread)
    std::pair<size_t,size_t> count_triangles_multi(size_t n_threads);
};

#endif
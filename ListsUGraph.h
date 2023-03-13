#ifndef ListsUGraph_H
#define ListsUGraph_H

#include <stddef.h>
#include <vector>
#include <tuple>
#include <string>
#include <future>
class ListsUGraph
{
private:
    size_t n_nodes=0;
    size_t n_edges=0;

    //read edges from file
    std::vector<std::pair<size_t,size_t>> edges;

    //creates lists data structure, populates it and sorts every list
    std::pair<std::vector<std::vector<size_t>>&,unsigned long long> _create_list();
    std::pair<std::vector<std::vector<size_t>>&,unsigned long long> _create_list_multi(size_t n_threads);

    //aux function for populating lists
    static void _populate_lists(std::vector<std::vector<size_t>> &lists,
                                std::vector<std::pair<size_t,size_t>> &edges,
                                std::vector<std::mutex> &mutexes,
                                size_t id=0, size_t skip=1);

    //aux function for sorting every list in lists
    static void _sort_lists(std::vector<std::vector<size_t>> &lists,size_t id=0, size_t skip=1);

    //given a ListsUGraph object, count the number of triangles the graph,
    //other two parameters are for multithread execution
    static unsigned long long _count_triangles(std::vector<std::vector<size_t>> &lists,
                                                std::vector<std::pair<size_t,size_t>> &edges,
                                                size_t id=0, size_t skip=1);

public:
    ListsUGraph(std::string dirname);

    //print edges
    void print_edges();

    //print graph variables and stats
    void print_variables();

    //count triangle of this object (single thread)
    std::tuple<unsigned long long,unsigned long long,unsigned long long> count_triangles();

    //count triangle of this object (multi thread)
    std::tuple<unsigned long long,unsigned long long,unsigned long long> count_triangles_multi(size_t n_threads);
};

#endif
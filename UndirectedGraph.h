#ifndef UndirectedGraph_H
#define UndirectedGraph_H

#include <iostream>
#include <vector>

class UndirectedGraph
{
protected:
    std::size_t n_nodes=0;
    size_t n_edges=0;

    //read edges from file
    std::vector<std::pair<size_t,size_t>> edges;

public:
    UndirectedGraph(std::string filename);
    
    //print edges
    void print_edges();

    //print graph variables and stats
    void print_variables();
};

#endif
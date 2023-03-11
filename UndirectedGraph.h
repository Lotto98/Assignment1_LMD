#ifndef UndirectedGraph_H
#define UndirectedGraph_H

#include <iostream>
#include <vector>

class UndirectedGraph
{
protected:
    size_t n_nodes=0;
    size_t n_edges=0;

    //read edges from file
    std::vector<std::pair<size_t,size_t>> edges;

public:
    
    //load undirected graph from file
    UndirectedGraph(std::string filename);
    
    //print edges
    void print_edges();

    //print graph variables and stats
    void print_variables();

};

#endif
#ifndef UndirectedGraph_H
#define UndirectedGraph_H

#include <iostream>
#include <vector>
#include <fstream>
#include <future>
using namespace std;

class UndirectedGraph
{
protected:
    size_t n_nodes=0;
    size_t n_edges=0;

    //read edges from file
    vector<pair<size_t,size_t>> edges;

public:
    UndirectedGraph(string filename);
    
    void print_edges();
    void print_variables();
};

#endif